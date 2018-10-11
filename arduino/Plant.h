#pragma once 

#include "Arduino.h"

class Plant
{
public:
	Plant(uint16_t humidity_when_dry, uint16_t pump_time);

	void update(uint32_t update_time, uint16_t humidity);

	void set_loose(uint32_t  time) { loose_time_ = time; }
	bool is_loose() { return loose_time_ != 0; }

	char state();

	uint16_t pump_time() { return pump_time_; }

	bool needs_water();

	void set_watered(uint32_t time) { watered_time = time; }

	uint16_t humidity() { return humidity_sensor_; }

private:
	uint16_t humidity_when_dry_ = 0;
	uint16_t pump_time_ = 0;
	uint32_t loose_time_ = 0;
	uint32_t update_time_ = 0;
	uint32_t watered_time = 0;
	uint16_t humidity_sensor_ = 0;
};
