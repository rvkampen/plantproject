#pragma once 

#include "arduino.h"
#include "sensor_type.h"

#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

class Report
{
public:
	Report(uint32_t unixtime, int sensorcount);

	void add(byte sensor, sensor_type type, float value);

	void printTo(String &s);
private:
	DynamicJsonBuffer jsonBuffer;
	JsonObject* root;
	JsonArray* measurements;
};
