#include "Report2.h"

Report::Report(uint32_t unixtime, byte sensorcount)
	: unixtime_(unixtime)
	, max_(sensorcount)
	, sensors_(new sensor_data[sensorcount])
{
}

void Report::add(sensor_type type, float value)
{
	if (count_ < max_)
	{
		sensors_[count_].type = type;
		sensors_[count_].value = value;
		++count_;
	}
}

void Report::printTo(String &s)
{
	Serial.print(F("constructing report with "));
	Serial.print(count_);
	Serial.println(F(" observations"));

	s.reserve(s.length() + 40 + count_ * 33);
	//char* buf = &s[s.length()];
	//char* begin = buf;
	//buf += sprintf(buf, "data={\"time\":%u,\"sensor\":[", count_);
	s.concat("data={\"time\":");
	s.concat(unixtime_);
	s.concat(",\"sensor\":[");
	for (byte i(0); i < count_; ++i)
	{
		//buf += sprintf(buf, "{\"sensor_type\":%u,\"value\":%s},", sensors_[i].type, String(sensors_[i].value, 2).c_str());
		s.concat("{\"sensor_type\":");
		s.concat(sensors_[i].type);
		s.concat(",\"value\":");
		s.concat(sensors_[i].value);
		s.concat("},");
	}
	if(count_)
		s.setCharAt(s.length()-1, ' ');
	s.concat("]}");
	//buf += sprintf(buf, "]}");
	//s.setCharAt(, 0);
}
