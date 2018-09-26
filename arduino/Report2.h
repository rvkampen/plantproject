#pragma once

#include "arduino.h"
#include "sensor_type.h"

struct sensor_data
{
	sensor_type type;
	float value;
};

class Report
{
public:
	Report(uint32_t unixtime, byte sensorcount);

	void add(sensor_type type, float value);

	void printTo(String &s);

private:
	uint32_t unixtime_ = 0;
	sensor_data * sensors_;
	byte max_ = 0;
	byte count_ = 0;
};
