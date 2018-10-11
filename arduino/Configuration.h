#pragma once

// start and end time of allowed watering time
constexpr auto START_HOUR = 8;
constexpr auto START_MINUTE = 0;
constexpr auto END_HOUR = 9;
constexpr auto END_MINUTE = 0;

// maximum timeout (ms) before we consider the hose to be loose
constexpr auto MAX_TIMEOUT = 10000;

// the bucket is like a normal plant, enter the index here
constexpr auto BUCKET_SENSOR_INDEX = 15;

constexpr auto BUCKET_SENSOR_WARNING = 400;
constexpr auto BUCKET_SENSOR_EMPTY = 600;


// enable the sensors you connected (I2C)
#define ENABLE_BLACKBOX
//#define ENABLE_BARO

// configure plants in Configuration.cpp

// -------------------------------------
#include "Plant.h"
Plant & get_plant(byte index);
byte get_plant_count();