#pragma once 

#include "arduino.h"

#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

class Report
{
public:
	Report(uint32_t unixtime, int sensorcount);

	void add(int sensor, int type, const String&value);

	void printTo(String &s);
private:
	DynamicJsonBuffer jsonBuffer;
	JsonObject* root;
	JsonArray* measurements;
};
