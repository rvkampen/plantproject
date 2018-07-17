#ifndef _TIME_h
#define _TIME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void time_init();

void time_update();

bool time_ok();
bool time_before(byte hour, byte minute);
const String & time_formatted();
const uint32_t & time_unixtimestamp();
const uint16_t & time_day();

uint16_t time_day_diff(uint32_t timestamp);

#endif
