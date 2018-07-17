#ifndef _REPORT_h
#define _REPORT_h

#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Report
{
public:
	Report(double unixtime, int sensorcount);

	void add(int sensor, int type, const String&value);

	void printTo(String &s);
private:
	DynamicJsonBuffer jsonBuffer;
	JsonObject* root;
	JsonArray* measurements;
};

#endif
