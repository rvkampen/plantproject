// airsensor.h

#ifndef _AIRSENSOR_h
#define _AIRSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void airsensor_update();

const String& humidity_formatted();
const String& temperature_formatted();

#endif

