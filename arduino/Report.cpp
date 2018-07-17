#include "Report.h"

Report::Report(double unixtime, int sensorcount)
	: jsonBuffer(JSON_ARRAY_SIZE(sensorcount) + JSON_OBJECT_SIZE(2) + sensorcount * JSON_OBJECT_SIZE(4))
{
	root= &jsonBuffer.createObject();
	root->set("time", unixtime);
	measurements = &root->createNestedArray("sensor");
}

void Report::add(int sensor, int t, const String & v) {
	JsonObject& measurement = measurements->createNestedObject();
	measurement.set("id", sensor);
	measurement.set("type", t);
	measurement.set("value", v);
}

void Report::printTo(String & s)
{
	(*root).printTo(s);
}
