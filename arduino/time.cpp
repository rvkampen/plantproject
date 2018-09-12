#include "time.h"
#include "pinout.h"

#include <DS3231.h>

DS3231 clock;

DateTime starttime_;
DateTime time_;
String formatted_;
uint32_t unixformat_;
bool time_ok_ = true;
uint16_t days_ = 0;

/*
// number of days since 2000/01/01, valid for 2001..2099
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
	if (y >= 2000)
		y -= 2000;
	uint16_t days = d;
	for (uint8_t i = 1; i < m; ++i)
		days += pgm_read_byte(daysInMonth + i - 1);
	if (m > 2 && y % 4 == 0)
		++days;
	return days + 365 * y + (y + 3) / 4 - 1;
}

static long time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
	return ((days * 24L + h) * 60 + m) * 60 + s;
}

static uint32_t unixtime(const Time & time) {
	uint32_t t;
	uint16_t days = date2days(time.year, time.mon, time.date);
	t = time2long(days, time.hour, time.min, time.sec);
	t += SECONDS_FROM_1970_TO_2000;  // seconds from 1970 to 2000

	return t;
}

*/
DateTime get_time()
{
	return RTClib::now();
}

String format_time(DateTime & t)
{
	char output[9];
	output[0] = t.hour()<10 ? 48 : char((t.hour() / 10) + 48);
	output[1] = char((t.hour() % 10) + 48);
	output[2] = 58;
	output[3] = t.minute()<10 ? 48 : char((t.minute() / 10) + 48);
	output[4] = char((t.minute() % 10) + 48);
	output[5] = 58;
	output[6] = t.second()<10 ? 48 : char((t.second() / 10) + 48);
	output[7] = char((t.second() % 10) + 48);
	output[8] = 0;
	return String(&output[0]);
}
/*

bool time_before(const Time & t, int hour, int minute)
{
	return (t.hour * 60 + t.min) < (hour * 60 + minute);
}
*/
void time_init(uint32_t timestamp)
{
	set_time(timestamp);
	starttime_ = time_ = get_time();
}

bool set_time(uint32_t timestamp)
{

	DateTime d(timestamp);

	Serial.print(F("Setting time to: "));
	Serial.print(format_time(d));
	Serial.print(F(" - "));
	Serial.print(d.year());
	Serial.print(F("/"));
	Serial.print(d.month());
	Serial.print(F("/"));
	Serial.print(d.day());
	Serial.print(F(" - day of week = "));
	Serial.println(d.dayOfTheWeek());

	if (d.year() < 2018)
		return false;

	Serial.print(F("set1"));
	clock.setClockMode(false);
	Serial.print(F("set2"));
	clock.setYear(d.year() - 2000);
	Serial.print(F("set3"));
	clock.setMonth(d.month());
	clock.setDate(d.day());
	clock.setDoW(d.dayOfTheWeek());
	clock.setHour(d.hour());
	clock.setMinute(d.minute());
	clock.setSecond(d.second());

	Serial.print(F("Done setting time"));

	return true;
}

void time_update()
{
	DateTime old = time_;
	time_ = get_time();
	time_ok_ = old.unixtime() < time_.unixtime();
	formatted_ = format_time(time_);
	unixformat_ = time_.unixtime();
	days_ = date2days(time_.year(), time_.month(), time_.day());
	Serial.print(F("Time: "));
	Serial.print(formatted_);
	Serial.print(F(" - "));
	Serial.print(time_.year());
	Serial.print(F("/"));
	Serial.print(time_.month());
	Serial.print(F("/"));
	Serial.print(time_.day());
	Serial.print(F("-"));
	Serial.println(time_.dayOfTheWeek());

	Serial.println(clock.getTemperature());
}
/*
bool time_ok()
{
	return false;
}

bool time_before(byte hour, byte minute)
{
	return time_before(time_, hour, minute);
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

uint16_t time_day_diff(uint32_t timestamp)
{
	return (unixformat_ - timestamp) / (24 * 3600);
}
*/