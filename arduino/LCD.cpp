#include "LCD.h"

#include <LiquidCrystal_I2C.h>

// LCD 5v:  SDA/SCL   -> Arduino Analog 4 & 5
LiquidCrystal_I2C lcd_(0x27, 16, 2);
//LiquidCrystal_I2C lcd_(0x27, 20, 4);

String lcd_top_("                ");
String lcd_state_("                ");

void lcd_init()
{
	lcd_.init();
	lcd_.backlight();
	lcd_.clear();
}

void lcd_debug()
{
	static bool first = true;
	if (first)
	{
		lcd_update_top("TI:ME", "XXC YY% ZZZZhPa");
		lcd_line(1, "     Line");
		lcd_update_state(0, 'T');
		lcd_update_state(1, 'e');
		lcd_update_state(2, 's');
		lcd_update_state(3, 't');
		lcd_state_ = "                ";
		first = false;
	}
	Serial.println(F(" -- LCD "));
	Serial.println(F("1234567890123456"));
	Serial.println(lcd_top_);
	Serial.println(lcd_state_);
}

void lcd_update_top(const String & time, const String & meteo)
{
	lcd_top_ = time + ' ' + ' ' + meteo;

	lcd_.setCursor(0, 0);
	lcd_.print(time + ' ' + ' ' + meteo);
}

void lcd_update_state(byte index, char state)
{
	lcd_state_[index] = state;

	lcd_.setCursor(index, 1);
	lcd_.print(state);
}

void lcd_line(uint8_t index, const String & val)
{
	lcd_.setCursor(0, index);
	lcd_.print(val);
}
