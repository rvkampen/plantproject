#include "Report.h"

Report::Report(uint32_t unixtime, int sensorcount)
	: jsonBuffer(JSON_ARRAY_SIZE(sensorcount) + JSON_OBJECT_SIZE(2) + sensorcount * JSON_OBJECT_SIZE(3))
{
	Serial.println(JSON_ARRAY_SIZE(sensorcount) + JSON_OBJECT_SIZE(2) + sensorcount * JSON_OBJECT_SIZE(3));
	root= &jsonBuffer.createObject();
	root->set("time",unixtime);
	measurements = &root->createNestedArray("sensor");
}

void Report::add(int sensor, int t, float v) {
	JsonObject& measurement = measurements->createNestedObject();
	measurement.set("id", sensor);
	measurement.set("type", t);
	measurement.set("value", v);
}

void Report::printTo(String & s)
{
	(*root).printTo(s);
}
