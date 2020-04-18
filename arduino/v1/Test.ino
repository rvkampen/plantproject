#include "pinout.h"
#include "plantsensor.h"
//#include "Report2.h"
//#include "time.h"
//#include "airsensor.h"
//#include "Plant.h"
//#include "HTTPPost.h"
//#include "NTP.h"


void setup()
{
	Serial.begin(115200);
	Serial.println(F("Starting..."));
	pin_init();

	//network_init();
	//airsensor_init();
	//ntp_init();
	//time_init(0);
	//plantsensor_init();

	Serial.println(F("Startup done!"));
}

void TestPump(int pump)
{
    Serial.print(F("Starting Pump "));
    Serial.print(pump);
    select_plant(pump);
    delay(100);
    Serial.print(F(" .."));

    unsigned long contact = 0, end_contact = 0;
    uint16_t hose_min = 1024, hose_max = 0;
    uint16_t hose_start = is_water_at_hose_end();

    if (hose_start > 400)
    {
        enable_pump();
        delay(2000);
        disable_pump();

        Serial.print(F(".. Stopped - hose was at start: "));
        Serial.print(hose_start);
        Serial.print(F(" ended at: "));
        Serial.print(is_water_at_hose_end());
        Serial.println(F(" - pumped 2 seconds."));
        return;
    }

    enable_pump();
    
    unsigned long start = millis();
    do {
        // measure
        uint16_t hose = is_water_at_hose_end();
        if (hose > hose_start + 100)
        {
            contact = millis();
            disable_pump();
        }
        if (hose < hose_min)
            hose_min = hose;
        if (hose > hose_max)
            hose_max = hose;
    } while (contact == 0 && millis() < start + 5000);

    disable_pump();
    
    if (contact)
    {
        do {
            // measure
            uint16_t hose = is_water_at_hose_end();
            if (hose < 100)
                end_contact = millis();

            if (hose > hose_max)
                hose_max = hose;

        } while (end_contact == 0 && millis() < contact + 5000);
    }

    uint16_t hose_end = is_water_at_hose_end();

    Serial.print(F(".. Stopped "));

    if (contact)
    {
        Serial.print(contact - start);
        Serial.print(F("ms"));
        if (end_contact)
        {
            Serial.print(F(", after "));
            Serial.print(end_contact - contact);
            Serial.print(F("ms "));
        }
        else
        {
            Serial.print(F(", no end "));
        }
    }
    else
        Serial.print(F("NO CONTACT "));

    Serial.print(F("range: "));
    Serial.print(hose_min);
    Serial.print(F(" - "));
    Serial.print(hose_max);
    Serial.print(F(" start: "));
    Serial.print(hose_start);
    Serial.print(F(" - end: "));
    Serial.println(hose_end);
}

void TestPumps(int max = 16)
{
    for (int i = 0; i < max; i++)
    {
        TestPump(i);
    }
}

void TestSensor(int sensor)
{
    Serial.print(F("Starting Sensor "));

    if(sensor < 10)
        Serial.print(" ");
    Serial.print(sensor);
    
    select_plant(sensor);
    
    Serial.print(F(" ... "));
    
    plantsensor_init();
    plantsensor_update();
    plantsensor_print();

    Serial.print(F("  Humidity: "));
    Serial.print(humidity_sensor());
    Serial.print(F("  Hose: "));
    Serial.print(is_water_at_hose_end());
    Serial.println(F(" ... End Sensor"));
}

void TestSensors(int max = 16)
{
    for (int i = 0; i < max; i++)
    {
        TestSensor(i);
    }
}


void loop()
{
    TestSensor(0);
    TestSensor(15);
    TestPump(0);
    select_plant(-1); // to turn off all sensors
    delay(10000);

	//time_update();
	//time_debug();
	//airsensor_update();
	//airsensor_debug();
    //TestSensors();
    //TestPumps();

	//String json = F("data=");
	//{// let our report go out of scope as soon as we have a report ready
	//	Report r(0, airsensor_count());
	//	airsensor_addtoreport(r);
	//	r.printTo(json);
	//}
	//
	//Serial.println(json);
	//
	//char serverName[] = "www.plantproject.dx.am";
	//char pageName[] = "/update.php";
	//http_post(serverName, 80, pageName, json);
	//
	//delay(30000);
}
