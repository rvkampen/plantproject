#ifndef _AIRSENSOR_h
#define _AIRSENSOR_h

#include "report.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void airsensor_update();
int airsensor_count();
void airsensor_addtoreport(Report & r);

const String& humidity_formatted();
const String& temperature_formatted();

#endif
