//#include "pinout.h"
//#include "Report2.h"
//#include "time.h"
//#include "airsensor.h"
#include "LCD.h"
//#include "Plant.h"
//#include "HTTPPost.h"
//#include "plantsensor.h"
//#include "NTP.h"


void setup()
{
	Serial.begin(115200);
	Serial.println(F("Starting..."));
	//network_init();
	//airsensor_init();
	//ntp_init();
	//time_init(0);
	//plantsensor_init();
	lcd_init();
	//
	//pinMode(PIN_A0, INPUT);
	//pinMode(PIN_A1, INPUT);
	//pinMode(PIN_A2, INPUT);
	//pin_init();
	Serial.println(F("Startup done!"));
}

void loop()
{
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
	delay(500);
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
