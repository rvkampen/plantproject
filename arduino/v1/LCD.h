#pragma once 

#include "Arduino.h"

void lcd_init();

void lcd_debug();

void lcd_update_top(const String& time, const String& meteo);

void lcd_update_state(byte index, char state);

void lcd_line(uint8_t index, const String& val);