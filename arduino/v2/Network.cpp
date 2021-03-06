#include "Network.h"
#include "State.h"
#include "debug.h"
#include "config.h"
#include "Time.h"
#include <Ethernet.h>
#include <ArduinoHttpClient.h>

EthernetClient network;

void network_init()
{
	// disable SD SPI
	pinMode(4, OUTPUT);
	digitalWrite(4, HIGH);

    // initialize network
    for (bool success = false; !success;)
    {
        DEBUG(F("Starting ethernet..."));
        const byte mac[] = { MAC };
        if (!Ethernet.begin(mac)) {//, 20000UL, 40000UL))
            DEBUGLN(F("failed"));
            delay(2000);
        }
        else
        {
            DEBUG(F(".."));
            delay(1000);
            DEBUGLN(Ethernet.localIP());
            success = Ethernet.localIP()[0] != 192;
        }
    }

    // todo find if this helps
    network.setTimeout(30 * 1000);
}

bool download_config()
{
    DEBUG_TRACKTIME
    DEBUGLN(F("GETing config"));
    HttpClient client = HttpClient(network, SERVERADDRESS, SERVERPORT);

    // todo find if this helps
    client.setTimeout(30 * 1000);

    client.beginRequest();
    if (client.get("/api/settings/" SETUP_ID) != HTTP_SUCCESS)
    {
        DEBUGLN(F("Failed to connect"));
        client.stop();
        return false;
    }
    //client.sendHeader("Host", SERVERADDRESS);
    client.sendHeader("Accept", "text/plain");
    client.sendHeader("Cache-Control", "no-cache");
    client.sendHeader("Accept-Encoding", "none");
    client.sendHeader("Connection", "Close");
    client.endRequest();
    DEBUGLN(F("Request send"));

    int statusCode = client.responseStatusCode();
    DEBUG(F("Status code: "));
    DEBUGLN(statusCode);

    if (statusCode != 200)
    {
        if (statusCode > 0) 
        {
            DEBUG(F("remaining response: "));
            DEBUGLN(client.responseBody());
        }
        client.stop();
        return false;
    }

    State.StartUpdate();

    //DEBUGLN(F("Headers: "));
    while (client.headerAvailable())
    {
        String headerName = client.readHeaderName();
        String headerValue = client.readHeaderValue();
        //DEBUGLN(headerName + ": " + headerValue);
        if (headerName == "ts")
            State.ProcessTimestamp(strtoul(headerValue.c_str(), NULL, 16));
    }

    //DEBUG(F("Content Length: "));
    //DEBUGLN(client.contentLength());

    int thing;
    do
    {
        thing = client.read();
        bool plant = thing == 'p';
        bool bucket = thing == 'b';
        if (plant || bucket)
        {
            char buff[23];
            int wantedlen = bucket ? 8 : 23;
            int len = client.readBytes(&buff[0], wantedlen);
            if (wantedlen != len)
            {
                DEBUG(F("Failed to read "));
                DEBUG((char)thing);
                DEBUG(": ");
                Serial.write(&buff[0], len);
                DEBUGLN();
                DEBUG(F("remaining response: "));
                DEBUGLN(client.responseBody());

                State.Cancel();
                client.stop();
                return false;
            }

            long id = strtol(&buff[1], NULL, 16);
            long lowlevel = strtol(&buff[4], NULL, 16);

            if (bucket)
            {
                State.ProcessBucket(id, lowlevel);
            }
            else
            {
                bool enabled = buff[9] == '1';
                long bucketid = strtol(&buff[11], NULL, 16);
                long pumptime = strtol(&buff[14], NULL, 16);
                long filltime = strtol(&buff[19], NULL, 16);

                State.ProcessPlant(id, lowlevel, enabled, bucketid, pumptime, filltime);
            }
        }
        else if (thing != '\r' && thing != '\n' && thing != ' ' && thing != -1)
        {
            DEBUG(F("Failed to parse "));
            DEBUGLN((char)thing);
            DEBUG(F("remaining response: "));
            DEBUGLN(client.responseBody());

            State.Cancel();
            client.stop();
            return false;
        }
    } while (thing != -1);

    State.Confirm();
    client.stop();
    return true;
}

bool upload_status()
{
    DEBUG_TRACKTIME
    HttpClient client = HttpClient(network, SERVERADDRESS, SERVERPORT);
    DEBUGLN(F("POSTing status"));

    //uint8_t bucket = 0;
    //uint8_t plant = 0;
    //for (const item & i : State.Items)
    //{
    //    bucket += i.isBucket;
    //    plant += i.isPlant;
    //}
    //int datalength = 12 + (SENSOR_COUNT * 15) + (bucket * 16) + (plant * 25);

    client.beginRequest();
    if (client.post("/api/status/" SETUP_ID) != HTTP_SUCCESS)
    {
        DEBUGLN(F("Failed to connect"));
        client.stop();
        return false;
    }
    
    client.sendHeader("Content-Type", "multipart/form-data; boundary=BOUND");
    //client.sendHeader("Content-Type", "application/x-www-form-urlencoded");
    //client.sendHeader("Content-Length", datalength);
    //client.sendHeader("X-Custom-Header", "custom-header-value");
    client.beginBody();

    client.println("--BOUND");
    client.println("Content-Disposition: form-data; name=\"update\"");
    client.println();

    client.print(SETUP_ID);
    client.print(' ');
    client.println(getTime(), 16);

    for (int i = 0; i < SENSOR_COUNT; i++)
    {
        client.print("s ");
        client.print(i, 16);
        client.print(' ');
        client.println(State.Sensors[i].value, 16);
    }

    for (int i = 0; i < ITEM_COUNT; i++)
    {
        const item & item = State.Items[i];
        if (item.isBucket)
            client.print('b');
        else if (item.isPlant)
            client.print('p');
        else
            continue;

        client.print(' ');
        client.print(i, 16);
        client.print(' ');
        client.print(item.actualWaterLevel, 16);
        client.print(' ');
        client.print(item.actualTemperature, 16);

        if (item.isPlant) 
        {
            client.print(' ');
            client.print(item.looseWarning);
            client.print(' ');
            client.print(item.wateredInLastGo);
            client.print(' ');
            client.print(item.actualPumpTime);
        }
        client.println();
    }
    client.println("--BOUND--");
    client.endRequest();

    // read the status code and body of the response
    int statusCode = client.responseStatusCode();

    DEBUG(F("Status code: "));
    DEBUGLN(statusCode);
    if (statusCode > 0)
    {
        DEBUG(F("Response: "));
        DEBUGLN(client.responseBody());
    }
    client.stop();
    return statusCode == 200;
}