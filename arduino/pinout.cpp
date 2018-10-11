#include "PinOut.h"

void pin_init()
{
	pinMode(SENSOR_HUMIDITY_PINA, INPUT);
	pinMode(PIEZO_PIN, OUTPUT);
	pinMode(SELECT_PIN0, OUTPUT);
	pinMode(SELECT_PIN1, OUTPUT);
	pinMode(SELECT_PIN2, OUTPUT);
	pinMode(SELECT_PIN3, OUTPUT);
	pinMode(SENSOR_ENABLE_PIN, OUTPUT);
	pinMode(PUMP_PIN, OUTPUT);
	pinMode(WATERFLOW_PIN, INPUT);

	digitalWrite(PIEZO_PIN, LOW);
	digitalWrite(SELECT_PIN0, LOW);
	digitalWrite(SELECT_PIN1, LOW);
	digitalWrite(SELECT_PIN2, LOW);
	digitalWrite(SELECT_PIN3, LOW);
	digitalWrite(SENSOR_ENABLE_PIN, LOW);
	digitalWrite(PUMP_PIN, LOW);
}

void pin_select_output(byte plant)
{
	digitalWrite(SELECT_PIN0, plant & 0x01);
	digitalWrite(SELECT_PIN1, plant & 0x02);
	digitalWrite(SELECT_PIN2, plant & 0x04);
	digitalWrite(SELECT_PIN3, plant & 0x08);
}