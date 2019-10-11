#pragma once

#include "Arduino.h"
#include "SensorType.h"

struct sensor_data
{
	sensor_type type;
	float value;
};

class Report
{
public:
	Report(uint32_t unixtime, byte sensorcount);
	~Report();

	void add(sensor_type type, float value);

	void printTo(String &s);

	static int max_length(byte sensorcount) { return 40 + sensorcount * 33; }

private:
	uint32_t unixtime_ = 0;
	sensor_data * sensors_;
	byte max_ = 0;
	byte count_ = 0;
};
