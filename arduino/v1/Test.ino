#include "pinout.h"
//#include "Report2.h"
//#include "time.h"
//#include "airsensor.h"
//#include "LCD.h"
//#include "Plant.h"
//#include "HTTPPost.h"
#include "plantsensor.h"
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
	//lcd_init();

	Serial.println(F("Startup done!"));
}

void TestPump(int pump)
{
    Serial.print(F("Starting Pump "));
    Serial.print(pump);
    select_plant(pump);
    enable_pump();
    Serial.print(F(" ... "));
    delay(2000);
    disable_pump();
    Serial.println(F("Stop!"));
}

void TestPumps(int max = 16)
{
    for (int i = 0; i < max; i++)
    {
        TestPump(i);
        delay(1000);
    }
    delay(2000);
}

void TestSensor(int sensor)
{
    Serial.print(F("Starting Sensor "));
    Serial.print(sensor);
    select_plant(sensor);
    Serial.println(F(" ... "));
    plantsensor_init();
    plantsensor_update();
    plantsensor_print();

    Serial.print(F("   Humidity: "));
    Serial.println(humidity_sensor());
    Serial.print(F("   Hose: "));
    Serial.println(is_water_at_hose_end());
    Serial.println(F("End Sensor!"));
}

void TestSensors(int max = 16)
{
    for (int i = 0; i < max; i++)
    {
        TestSensor(i);
    }
    delay(1000);
}


void loop()
{
    TestSensor(1);
    TestSensor(15);
    //lcd_line(0, "TEST");
	//time_update();
	//time_debug();
	//airsensor_update();
	//airsensor_debug();
	//Serial.println("test0");
	//plantsensor_update();
	////Serial.println("test1");
	//for (uint8_t i = 0; i < plantsensor_count(); i++)
	//{
	//	lcd_line(i, plantsensor_formatted(i)+String(" ")+String(analogRead(i)));
	//	Serial.println(plantsensor_formatted(i));
	//}
	//delay(500);
	//Serial.println("test2");

	//lcd_update_top("--:--", humidity_formatted(), temperature_formatted());

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
