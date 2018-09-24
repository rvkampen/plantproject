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
constexpr auto PIEZO_PIN = 6;
constexpr auto SELECT_PIN0 = 7;
constexpr auto SELECT_PIN1 = 8;
constexpr auto SELECT_PIN2 = 9;
constexpr auto SELECT_PIN3 = 10;
constexpr auto SENSOR_ENABLE_PIN = 11;
constexpr auto PUMP_PIN = 12;
constexpr auto WATERFLOW_PIN = 13;

void pin_init();
