#include "LCD.h"

#include <LiquidCrystal_I2C.h>

// LCD 5v:  SDA/SCL   -> Arduino Analog 4 & 5
//LiquidCrystal_I2C lcd_(0x27, 16, 2);
LiquidCrystal_I2C lcd_(0x27, 20, 4);

void lcd_init()
{
	lcd_.init();
	lcd_.backlight();
	lcd_.clear();
}

void lcd_update_top(const String & time, const String & meteo)
{
	lcd_.setCursor(0, 0);
	lcd_.print(time + ' ' + meteo);
}

void lcd_update_state(byte index, char state)
{
	lcd_.setCursor(index, 1);
	lcd_.print(state);
}

void lcd_line(uint8_t index, const String & val)
{
	lcd_.setCursor(0, index);
	lcd_.print(val);
}
