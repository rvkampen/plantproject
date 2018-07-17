#include "LCD.h"

#include <LiquidCrystal_I2C.h>

// LCD 5v:  SCL/SDA   -> Arduino Analog 4 & 5
LiquidCrystal_I2C lcd_(0x27, 16, 2);

void lcd_init()
{
	lcd_.init();
	lcd_.backlight();
	lcd_.clear();
}

void lcd_update_top(const String & time, const String & humidity, const String & temperature)
{
	lcd_.setCursor(0, 0);
	lcd_.print(time + ' ' + humidity + '%' + temperature + 'C');
}

void lcd_update_state(byte index, char state)
{
	lcd_.setCursor(index, 1);
	lcd_.print(state);
}
