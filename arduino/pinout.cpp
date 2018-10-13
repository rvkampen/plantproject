#include "PinOut.h"
#include "Configuration.h"

void pin_init()
{
	pinMode(SENSOR_HUMIDITY_PINA, INPUT);
	pinMode(PIEZO_PIN, OUTPUT);
	pinMode(SELECT_PIN0, OUTPUT);
	pinMode(SELECT_PIN1, OUTPUT);
	pinMode(SELECT_PIN2, OUTPUT);
	pinMode(SELECT_PIN3, OUTPUT);
	pinMode(SELECT_DISABLE_PIN, OUTPUT);
	pinMode(PUMP_PIN, OUTPUT);
	pinMode(WATERFLOW_PIN, INPUT);

	digitalWrite(PIEZO_PIN, LOW);
	digitalWrite(SELECT_PIN0, LOW);
	digitalWrite(SELECT_PIN1, LOW);
	digitalWrite(SELECT_PIN2, LOW);
	digitalWrite(SELECT_PIN3, LOW);
	digitalWrite(SELECT_DISABLE_PIN, HIGH); // high is disabled
	digitalWrite(PUMP_PIN, LOW);
}

void pin_select_output(byte plant)
{
	digitalWrite(SELECT_DISABLE_PIN, HIGH);
	digitalWrite(SELECT_PIN0, plant & 0x01);
	digitalWrite(SELECT_PIN1, plant & 0x02);
	digitalWrite(SELECT_PIN2, plant & 0x04);
	digitalWrite(SELECT_PIN3, plant & 0x08);
	digitalWrite(SELECT_DISABLE_PIN, LOW);
}

void read_plant_sensor(uint16_t & humidity_sensor)
{
	humidity_sensor = analogRead(SENSOR_HUMIDITY_PIN);
}

void enable_pump()
{
	digitalWrite(PUMP_PIN, HIGH);
}

void disable_pump()
{
	digitalWrite(PUMP_PIN, LOW);
}

bool is_water_at_hose_end()
{
	return digitalRead(WATERFLOW_PIN);
}

void pin_debug()
{
	for (int i = 0; i < get_plant_count(); i++)
	{
		pin_select_output(i);
		uint16_t humidity_sensor;
		read_plant_sensor(humidity_sensor);
		Serial.print(" -- Plant ");
		Serial.print(i);
		Serial.print(" humidity ");
		Serial.print(humidity_sensor);
		Serial.print(" hose end ");
		Serial.println(is_water_at_hose_end());
	}

	pin_select_output(BUCKET_SENSOR_INDEX);
	uint16_t humidity_sensor;
	read_plant_sensor(humidity_sensor);
	Serial.print(" -- bucket ");
	Serial.print(BUCKET_SENSOR_INDEX);
	Serial.print(" humidity ");
	Serial.println(humidity_sensor);
}