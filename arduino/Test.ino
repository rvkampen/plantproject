#include "pinout.h"
#include "Report2.h"
#include "time.h"
#include "airsensor.h"
#include "LCD.h"
#include "Plant.h"
#include "HTTPPost.h"
#include "NTP.h"


void setup()
{
	Serial.begin(115200);
	Serial.println(F("Starting..."));
	//network_init();
	airsensor_init();
	//ntp_init();
	//time_init(ntp_request_time_safe());

	//lcd_init();
	//pin_init();
	Serial.println(F("Startup done!"));
}

void loop()
{
	//time_update();
	Serial.println("test0");
	airsensor_update();
	Serial.println("test1");
	Serial.println(temperature_formatted());
	Serial.println("test2");

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
