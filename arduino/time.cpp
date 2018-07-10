#include "time.h"
#include "pinout.h"

#include <DS1302.h>

// DS1302:  RST pin   -> Arduino Digital 2
// (3.3v)   DAT pin   -> Arduino Digital 3
//          CLK pin   -> Arduino Digital 4
DS1302 clock(CLOCK_RST_PIN, CLOCK_DAT_PIN, CLOCK_CLK_PIN);

Time starttime_;
Time time_;
String formatted_;
uint32_t unixformat_;
bool time_ok_ = true;
uint16_t days_ = 0;

#define SECONDS_FROM_1970_TO_2000 946684800
const uint8_t daysInMonth[] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 };

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

Time get_time()
{
	return clock.getTime();
}

String format_time(Time & t)
{
	char output[9];
	output[0] = t.hour<10 ? 48 : char((t.hour / 10) + 48);
	output[1] = char((t.hour % 10) + 48);
	output[2] = 58;
	output[3] = t.min<10 ? 48 : char((t.min / 10) + 48);
	output[4] = char((t.min % 10) + 48);
	output[5] = 58;
	output[6] = t.sec<10 ? 48 : char((t.sec / 10) + 48);
	output[7] = char((t.sec % 10) + 48);
	output[8] = 0;
	return String(&output[0]);
}

bool time_before(const Time & t, int hour, int minute)
{
	return (t.hour * 60 + t.min) < (hour * 60 + minute);
}

void time_init()
{
	/*
	rtc.halt(false);
	rtc.writeProtect(false);
	rtc.setDOW(WEDNESDAY);
	rtc.setDate(16, 5, 2018);
	rtc.setTime(1, 1, 30);
	rtc.writeProtect(true);//*/

	starttime_ = time_ = get_time();
}

void time_update()
{
	Time old = time_;
	time_ = get_time();
	time_ok_ = unixtime(old) < unixtime(time_);
	formatted_ = format_time(time_);
	unixformat_ = unixtime(time_);
	days_ = date2days(time_.year, time_.mon, time_.date);
}

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
