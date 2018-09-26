#include "Report2.h"

Report::Report(uint32_t unixtime, byte sensorcount)
	: unixtime_(unixtime)
	, max_(sensorcount)
	, sensors_(new sensor_data[sensorcount])
{
}

Report::~Report()
{
	delete[] sensors_;
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
	Serial.print(F("report "));
	Serial.print(count_);
	Serial.println(F(" obs"));

	byte op = 0;
	byte op_succes = 0;
	//char* buf = &s[s.length()];
	//char* begin = buf;
	//buf += sprintf(buf, "data={\"time\":%u,\"sensor\":[", count_);
	op++; op_succes += s.concat("data={\"time\":");
	op++; op_succes += s.concat(unixtime_);
	op++; op_succes += s.concat(",\"sensor\":[");
	for (byte i(0); i < count_; ++i)
	{
		//buf += sprintf(buf, "{\"sensor_type\":%u,\"value\":%s},", sensors_[i].type, String(sensors_[i].value, 2).c_str());
		op++; op_succes += s.concat("{\"sensor_type\":");
		op++; op_succes += s.concat(sensors_[i].type);
		op++; op_succes += s.concat(",\"value\":");
		op++; op_succes += s.concat(sensors_[i].value);
		op++; op_succes += s.concat("},");
	}
	if (count_)
		s.setCharAt(s.length() - 1, ' ');
	op++; op_succes += s.concat("]}");
	//buf += sprintf(buf, "]}");
	//s.setCharAt(, 0);


	Serial.print(F("len "));
	Serial.print(s.length());
	Serial.print(F(" fail "));
	Serial.println(op- op_succes);
}
