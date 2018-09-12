#pragma once 

#include "arduino.h"

void lcd_init();

void lcd_update_top(const String& time, const String&humidity, const String&temperature);

void lcd_update_state(byte index, char state);
