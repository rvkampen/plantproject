#pragma once 

#include "arduino.h"

void time_init(uint32_t timestamp);

bool set_time(uint32_t timestamp);

void time_update();

bool time_ok();
bool time_before(byte hour, byte minute);
const String & time_formatted();
const uint32_t & time_unixtimestamp();
const uint16_t & time_day();

uint16_t time_day_diff(uint32_t timestamp);
