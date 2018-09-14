#include "time.h"
#include "pinout.h"

#include <DS3231.h>

// state variables
DS3231 clock;
DateTime starttime_;
DateTime time_;
String formatted_;
uint32_t unixformat_ = 0;
uint16_t days_ = 0;
bool time_ok_ = true;
float temp_ = 0;

// util
String format_time(const DateTime & t)
{
	char output[9];
	output[0] = t.hour()<10 ? '0' : char((t.hour() / 10) + '0');
	output[1] = char((t.hour() % 10) + '0');
	output[2] = ':';
	output[3] = t.minute()<10 ? '0' : char((t.minute() / 10) + '0');
	output[4] = char((t.minute() % 10) + '0');
	output[5] = ':';
	output[6] = t.second()<10 ? '0' : char((t.second() / 10) + '0');
	output[7] = char((t.second() % 10) + '0');
	output[8] = 0;
	return String(&output[0]);
}
String format_time(uint32_t timestamp)
{
	return format_time(DateTime(timestamp));
}
String format_date(const DateTime & t)
{
	char output[11];
	sprintf(&output[0], "%d/%2d/%2d", t.day(), t.month(), t.year());
	return String(&output[0]);
}
String format_date(uint32_t timestamp)
{
	return format_date(DateTime(timestamp));
}

// maintain
void time_init(uint32_t timestamp)
{
	set_time(timestamp);
	starttime_ = time_ = RTClib::now();
}

bool set_time(uint32_t timestamp)
{
	DateTime d(timestamp);
	Serial.print(F("Setting time to: "));
	Serial.print(format_date(d));
	Serial.print(F(" - "));
	Serial.print(format_time(d));
	Serial.print(F(" - day of week = "));
	Serial.println(d.dayOfTheWeek());

	if (d.year() >= 2018) // don't care about the past
	{
		clock.setClockMode(false);
		clock.setYear(d.year() - 2000);
		clock.setMonth(d.month());
		clock.setDate(d.day());
		clock.setDoW(d.dayOfTheWeek());
		clock.setHour(d.hour());
		clock.setMinute(d.minute());
		clock.setSecond(d.second());
		Serial.println(F("Done setting time"));

		time_update();
		time_ok_ = true; // reset state, we're sure of it, well sort of...
		return true;
	}
	else
	{
		Serial.println(F("Not a valid time"));
		time_update();
		return false;
	}
}

void time_update()
{
	DateTime old = time_;
	time_ = RTClib::now();
	time_ok_ &= old.unixtime() < time_.unixtime(); // time should only go forward
	formatted_ = format_time(time_);
	unixformat_ = time_.unixtime();
	days_ = date2days(time_.year(), time_.month(), time_.day());
	temp_ = clock.getTemperature();
	Serial.print(F("Time: "));
	Serial.print(format_date(time_));
	Serial.print(F("-"));
	Serial.print(formatted_);
	Serial.print(F("-day of week: "));
	Serial.print(time_.dayOfTheWeek());
	Serial.print(F("-temp: "));
	Serial.println(temp_);
}

// state
bool time_ok()
{
	return time_ok_;
}

const String & time_formatted()
{
	return formatted_;
}

const uint32_t & time_unixtimestamp()
{
	return unixformat_;
}

const uint16_t & time_day()
{
	return days_;
}

float clock_temperature()
{
	return temp_;
}

uint16_t time_day_diff(uint32_t timestamp)
{
	return (unixformat_ - timestamp) / (24 * 3600);
}

bool time_before(byte hour, byte minute)
{
	return (time_.hour() * 60 + time_.minute()) < (hour * 60 + minute);
}
