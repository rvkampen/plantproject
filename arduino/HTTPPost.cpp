#include "HTTPPost.h"

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

// set this to the number of milliseconds delay
// this is 30 seconds
#define delayMillis 30000UL

void http_init()
{
	// disable SD SPI
	pinMode(4, OUTPUT);
	digitalWrite(4, HIGH);

	Serial.print(F("Starting ethernet..."));
	if (!Ethernet.begin(mac))
		Serial.println(F("failed"));
	else
		Serial.println(Ethernet.localIP());

	delay(2000);
	Serial.println(F("Ready"));
}

bool http_post(char* domainBuffer, int remoteport, char* page, const String& data)
{
	// If using a static IP, comment out the next line
	Ethernet.maintain();

	int inChar;
	char outBuf[64];

	Serial.print(F("connecting..."));

	if (client.connect(domainBuffer, remoteport) == 1)
	{
		Serial.println(F("connected"));

		// send the header
		sprintf(outBuf, "POST %s HTTP/1.1", page);
		client.println(outBuf);
		sprintf(outBuf, "Host: %s", domainBuffer);
		client.println(outBuf);
		client.println(F("Connection: close\r\nContent-Type: application/x-www-form-urlencoded"));
		sprintf(outBuf, "Content-Length: %u\r\n", data.length());
		client.println(outBuf);

		// send the body (variables)
		client.print(data);
	}
	else
	{
		Serial.println(F("failed"));
		return false;
	}

	int connectLoop = 0;

	while (client.connected())
	{
		while (client.available())
		{
			inChar = client.read();
			Serial.write(inChar);
			connectLoop = 0;
		}

		delay(1);
		connectLoop++;
		if (connectLoop > 10000)
		{
			Serial.println();
			Serial.println(F("Timeout"));
			client.stop();
		}
	}

	Serial.println();
	Serial.println(F("disconnecting."));
	client.stop();
	return true;
}