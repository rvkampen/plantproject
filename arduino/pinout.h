#pragma once 

#include "arduino.h"

//------------PIN SETUP----------------------
// analog
constexpr auto SENSOR_TOP_PIN = 0;
constexpr auto SENSOR_TOP_PINA = PIN_A0;
constexpr auto SENSOR_BOTTOM_PIN = 1;
constexpr auto SENSOR_BOTTOM_PINA = PIN_A1;
// pin 4 & 5 are used for I2C

//digital
// 0 & 1 are used for serial communication
constexpr auto PIEZO_PIN = 2;
constexpr auto SELECT_PIN0 = 3;
constexpr auto SELECT_PIN1 = 4;
constexpr auto SELECT_PIN2 = 5;
constexpr auto SELECT_PIN3 = 6;
constexpr auto SENSOR_ENABLE_PIN = 7;
constexpr auto PUMP_PIN = 8;
constexpr auto WATERFLOW_PIN = 9;

void pin_init();
