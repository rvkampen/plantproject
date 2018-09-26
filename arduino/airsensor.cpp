#include "airsensor.h"

#include <Wire.h>

#define ENABLE_BLACKBOX
#define ENABLE_BARO

#ifdef ENABLE_BLACKBOX
	#include <AM2320.h>
	AM2320 blackbox_;
	char blackbox_state_;
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
	baro_pressure_ = baro_.getPressure()/100.0;
#endif
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

const String humidity_formatted()
{
#ifdef ENABLE_BLACKBOX
	return String(blackbox_.h, 1);
#else
	return String("--");
#endif
}

const String temperature_formatted()
{
#ifdef ENABLE_BLACKBOX
	return String(blackbox_.t, 1);
#elif defined(ENABLE_BARO)
	return String(baro_temperature_, 1);
#else
	return String("--");
#endif
}

const String pressure_formatted()
{
#ifdef ENABLE_BARO
	return String(baro_pressure_, 0);
#else
	return String("----");
#endif
}
