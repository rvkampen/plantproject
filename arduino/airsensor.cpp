#include "airsensor.h"

#include <Wire.h>
#include <AM2320.h>

AM2320 blackbox;

String humidity_, temperature_;

int airsensor_count()
{
	return 2; // total number of observations
}

void airsensor_addtoreport(Report & r) {

	r.add(1, 1, temperature_formatted());
	r.add(1, 2, humidity_formatted());
}

void airsensor_update() {


	switch (blackbox.Read()) {
	case 2:
		humidity_ = temperature_ = F("C!");
		break;
	case 1:
		humidity_ = temperature_ = F("--");
		break;
	case 0:
		humidity_ = String(blackbox.h, 1);
		temperature_ = String(blackbox.t, 1);
		break;
	}
}

const String & humidity_formatted()
{
	return humidity_;
}

const String & temperature_formatted()
{
	return temperature_;
}
