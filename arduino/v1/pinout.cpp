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
	pinMode(SELECT_DISABLE_PIN, OUTPUT);
	pinMode(PUMP_PIN, OUTPUT);

	digitalWrite(PIEZO_PIN, LOW);
	digitalWrite(SELECT_PIN0, LOW);
	digitalWrite(SELECT_PIN1, LOW);
	digitalWrite(SELECT_PIN2, LOW);
	digitalWrite(SELECT_PIN3, LOW);
	digitalWrite(SELECT_DISABLE_PIN, HIGH); // high is disabled
    disable_pump();
}

void select_plant(byte plant)
{
	digitalWrite(SELECT_DISABLE_PIN, HIGH);
	digitalWrite(SELECT_PIN0, plant & 0x01);
	digitalWrite(SELECT_PIN1, plant & 0x02);
	digitalWrite(SELECT_PIN2, plant & 0x04);
	digitalWrite(SELECT_PIN3, plant & 0x08);
	digitalWrite(SELECT_DISABLE_PIN, LOW);
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

void pin_debug()
{
	for (int i = 0; i < 1/*get_plant_count()*/; i++)
	{
		select_plant(i);
		uint16_t humidity = humidity_sensor();
		Serial.print(" -- Plant ");
		Serial.print(i);
		Serial.print(" humidity ");
		Serial.print(humidity);
		Serial.print(" hose end ");
		Serial.println(is_water_at_hose_end());
	}

	select_plant(BUCKET_SENSOR_INDEX);
    uint16_t humidity = humidity_sensor();
	Serial.print(" -- bucket ");
	Serial.print(BUCKET_SENSOR_INDEX);
	Serial.print(" humidity ");
	Serial.print(humidity);
    Serial.print(" hose end ");
    Serial.println(is_water_at_hose_end());
}