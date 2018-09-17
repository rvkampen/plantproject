#pragma once

#include "arduino.h"
#include "sensor_type.h"

struct sensor_data
{
	byte sensor;
	sensor_type type;
	float value;
};

class Report
{
public:
	Report(uint32_t unixtime, byte sensorcount)
		: unixtime_(unixtime)
		, max_(sensorcount)
		, sensors_(new sensor_data[sensorcount])
	{
	}

	void add(byte sensor, sensor_type type, float value)
	{
		if (count_ < max_) 
		{
			sensors_[count_].sensor = sensor;
			sensors_[count_].type = type;
			sensors_[count_].value = value;
			++count_;
		}
	}

	void printTo(String &s)
	{
		s.reserve(s.length() + 25 + count_ * 27);
		char* buf = &s[s.length()];
		buf += sprintf(buf, "{time:\"%u\",sensor:[", count_);
		for (byte i(0); i < count_; ++i)
			buf += sprintf(buf, "{id:%u,type:%u,value:%s}", sensors_[i].sensor, sensors_[i].type, String(sensors_[i].value, 2).c_str());
		buf += sprintf(buf, "]}");
	}

private:
	uint32_t unixtime_ = 0;
	sensor_data * sensors_;
	byte max_ = 0;
	byte count_ = 0;
};
