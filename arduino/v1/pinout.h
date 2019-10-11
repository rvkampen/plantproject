#pragma once 

#include "Arduino.h"

//------------PIN SETUP----------------------
// analog
constexpr auto SENSOR_HUMIDITY_PIN = PIN_A0;
constexpr auto SENSOR_TEMPERATURE_PIN = PIN_A1;
constexpr auto SENSOR_HOSE_END_PIN = PIN_A2;
// pin 4 & 5 are used for I2C

//digital
// 0 & 1 are used for serial communication
constexpr auto SELECT_PIN0 = 2;
constexpr auto SELECT_PIN1 = 3;
constexpr auto SELECT_PIN2 = 4;
constexpr auto SELECT_PIN3 = 5;
constexpr auto PUMP_PIN = 6;
constexpr auto PIEZO_PIN = 7;
constexpr auto SELECT_DISABLE_PIN = 8;
// 10 - 13 are used by SPI (sd & network)

void pin_init();

void select_plant(byte plant);

uint16_t humidity_sensor();
void enable_pump();
void disable_pump();
uint16_t is_water_at_hose_end();

void pin_debug();
