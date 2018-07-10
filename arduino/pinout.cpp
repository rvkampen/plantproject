#include "pinout.h"

void pin_init() {
	pinMode(SENSOR_TOP_PINA, INPUT);
	pinMode(SENSOR_BOTTOM_PINA, INPUT);
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
