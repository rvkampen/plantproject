#include "PinOut.h"
#include "Configuration.h"

void pin_init()
{
    // sensors
    pinMode(SENSOR_HUMIDITY_PIN, INPUT);
    pinMode(SENSOR_TEMPERATURE_PIN, INPUT);
    pinMode(SENSOR_HOSE_END_PIN, INPUT);

	pinMode(PIEZO_PIN, OUTPUT);
	pinMode(SELECT_PIN0, OUTPUT);
	pinMode(SELECT_PIN1, OUTPUT);
	pinMode(SELECT_PIN2, OUTPUT);
	pinMode(SELECT_PIN3, OUTPUT);
	pinMode(SENSOR_POWER_PIN, OUTPUT);
	pinMode(PUMP_PIN, OUTPUT);

	digitalWrite(PIEZO_PIN, LOW);
	digitalWrite(SELECT_PIN0, LOW);
	digitalWrite(SELECT_PIN1, LOW);
	digitalWrite(SELECT_PIN2, LOW);
	digitalWrite(SELECT_PIN3, LOW);
	digitalWrite(SENSOR_POWER_PIN, LOW); // high is disabled
    disable_pump();
}

void select_plant(byte plant)
{
	digitalWrite(SENSOR_POWER_PIN, LOW);
	digitalWrite(SELECT_PIN0, plant & 0x01);
	digitalWrite(SELECT_PIN1, plant & 0x02);
	digitalWrite(SELECT_PIN2, plant & 0x04);
	digitalWrite(SELECT_PIN3, plant & 0x08);
	digitalWrite(SENSOR_POWER_PIN, HIGH);
}

uint16_t humidity_sensor()
{
	 return analogRead(SENSOR_HUMIDITY_PIN);
}

void enable_pump()
{
	digitalWrite(PUMP_PIN, LOW);
}

void disable_pump()
{
	digitalWrite(PUMP_PIN, HIGH);
}

uint16_t is_water_at_hose_end()
{
	return analogRead(SENSOR_HOSE_END_PIN) ;
}
