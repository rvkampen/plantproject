#include "Configuration.h"
#include "AirSensor.h"
#include "HTTPPost.h"
#include "LCD.h"
#include "NTP.h"
#include "Report2.h"
#include "Time.h"

void setup()
{
	Serial.begin(115200);
	Serial.println(F("Starting..."));
	network_init();
	airsensor_init();
	ntp_init();
	time_init(ntp_request_time_safe());

	//lcd_init();
	//pin_init();
	Serial.println(F("Startup done!"));
}

void loop()
{
	time_update();
	airsensor_update();
	//lcd_update_top("--:--", humidity_formatted(), temperature_formatted());

	byte sensor_count = airsensor_count() + 1;
	String json;
	json.reserve(Report::max_length(sensor_count));
	{
		// let our report go out of scope as soon as we have a report ready
		Report r(time_unixtimestamp(), sensor_count);

		airsensor_addtoreport(r);

		if (time_clock_temperature() > 1) // only send it when its valid
			r.add(clock_temperature, time_clock_temperature());

		r.printTo(json);
	}

	Serial.println(json);

	char serverName[] = "www.plantproject.dx.am";
	char pageName[] = "/update.php";
	http_post(serverName, 80, pageName, json);

	delay(30000);
}