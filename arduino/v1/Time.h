#pragma once 

#include "Arduino.h"

// util
String format_time(uint32_t timestamp, bool seconds = true, char sep = ':');
String format_date(uint32_t timestamp);

// maintain time
void time_init(uint32_t timestamp);
bool time_set(uint32_t timestamp);
void time_update();
void time_debug();

// state
bool time_ok();
bool time_before(byte hour, byte minute);
const String & time_formatted();
const uint32_t & time_unixtimestamp();
const uint16_t & time_day();
uint16_t time_day_diff(uint32_t timestamp);
float time_clock_temperature();
