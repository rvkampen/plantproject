#include "AirSensor.h"
#include "Report2.h"
#include "Configuration.h"

#include <Wire.h>

#ifdef ENABLE_BLACKBOX
	#include <AM2320.h>
	AM2320 blackbox_;
	int8_t blackbox_state_;
#endif

#ifdef ENABLE_BARO
	#include <Seeed_BMP280.h>
	BMP280 baro_;
	float baro_temperature_, baro_pressure_;
#endif

void airsensor_init()
{
#ifdef ENABLE_BARO
	baro_.init();
#endif
}

void airsensor_update()
{
#ifdef ENABLE_BLACKBOX
	blackbox_state_ = blackbox_.Read();
#endif
#ifdef ENABLE_BARO
	baro_temperature_ = baro_.getTemperature();
	baro_pressure_ = baro_.getPressure() / 100.0;
#endif
}

void airsensor_debug()
{
	Serial.print(" -- airsensor state");
#ifdef ENABLE_BLACKBOX
	Serial.print(" -- Blackbox ");
	Serial.print(blackbox_state_);
	if (blackbox_state_ == 0)
	{
		Serial.print(" temperature: ");
		Serial.print(blackbox_.t);
		Serial.print(" humidity: ");
		Serial.print(blackbox_.h);
	}
#endif
#ifdef ENABLE_BARO
	Serial.print(" -- Baro ");
	Serial.print(" temperature: ");
	Serial.print(baro_temperature_);
	Serial.print(" pressure: ");
	Serial.println(baro_pressure_);
#endif
	Serial.println(" -- ");
}

int airsensor_count()
{
	// total number of observations
	return 0
#ifdef ENABLE_BLACKBOX
			+ 2
#endif
#ifdef ENABLE_BARO
			+ 2
#endif
	;
}

void airsensor_addtoreport(Report & r)
{
#ifdef ENABLE_BLACKBOX
	if (blackbox_state_ == 0) 
	{
		r.add(blackbox_temperature, blackbox_.t);
		r.add(blackbox_humidity, blackbox_.h);
	}
#endif
#ifdef ENABLE_BARO
	r.add(baro_temperature, baro_temperature_);
	r.add(baro_pressure, baro_pressure_);
#endif
}

const String airsensor_display()
{
	String result;

#ifdef ENABLE_BLACKBOX
	result += String(blackbox_.t, 1);
	result += "C ";
#elif defined(ENABLE_BARO)
	result += String(baro_temperature_, 1);
	result += "C ";
#endif

#ifdef ENABLE_BLACKBOX
	result += String(blackbox_.h, 0);
	result += "% ";
#endif

#ifdef ENABLE_BARO
	result += String(baro_pressure_, 0);
	result += "hPa";
#endif
	return result;
}
