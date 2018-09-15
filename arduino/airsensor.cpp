#include "airsensor.h"

#include <Wire.h>
#include <AM2320.h>
#include <Seeed_BMP280.h>

AM2320 blackbox;
BMP280 baro;

char black_state;
float temperature2_, pressure_ ;

void airsensor_init()
{
	baro.init();
}

void airsensor_update() 
{
	black_state = blackbox.Read();
	temperature2_ = baro.getTemperature();
	pressure_ = baro.getPressure()/100.0;
}

int airsensor_count()
{
	return 4; // total number of observations
}

void airsensor_addtoreport(Report & r)
{
	if (black_state == 0) 
	{
		r.add(1, 1, blackbox.t);
		r.add(1, 2, blackbox.h);
	}
	r.add(3, 1, temperature2_);
	r.add(3, 3, pressure_);
}

const String humidity_formatted()
{
	return String(blackbox.h, 1);
}

const String temperature_formatted()
{
	return String(blackbox.t, 1);
}
