//#include "pinout.h"
#include "time.h"
//#include "airsensor.h"
//#include "LCD.h"
//#include "Plant.h"
//#include "Report.h"
#include "HTTPPost.h"
#include "NTP.h"


void setup()
{
	Serial.begin(115200);
	Serial.println(F("initializing..."));
	//lcd_init();
	//pin_init();
	network_init();
	ntp_init();
	time_init(ntp_time_safe());
	Serial.println(F("ready to go!"));
}

void loop()
{
	time_update();
	//airsensor_update();
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
