#ifndef _LCD_h
#define _LCD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void lcd_init();

void lcd_update_top(const String& time, const String&humidity, const String&temperature);

void lcd_update_state(byte index, char state);

#endif

