#pragma once

// start and end time of allowed watering time
constexpr auto START_HOUR = 8;
constexpr auto START_MINUTE = 0;
constexpr auto END_HOUR = 9;
constexpr auto END_MINUTE = 0;

// maximum timeout (ms) before we consider the hose to be loose
constexpr auto MAX_TIMEOUT = 10000;

// the bucket is like a normal plant and has two sensors (top = warning level, bottom = error level)
constexpr auto BUCKET_SENSOR = 15;

// enable the sensors you connected (I2C)
#define ENABLE_BLACKBOX
#define ENABLE_BARO

// configure plants in Configuration.cpp

// -------------------------------------
#include "Plant.h"
Plant & get_plant(byte index);
byte get_plant_count();