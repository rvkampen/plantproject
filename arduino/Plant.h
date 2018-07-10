#ifndef _PLANT_h
#define _PLANT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

enum leading_sensor
{
	leading_sensor_top,
	leading_sensor_bottom,
	leading_sensor_average
};

class Plant
{
public:
	Plant(leading_sensor l, uint16_t drylevel, uint16_t pump_time);

	void update(uint32_t update_time, uint16_t top_sensor, uint16_t bottom_sensor);

	void set_loose(uint32_t  time) { loose_time_ = time; }
	bool is_loose() { return loose_time_ != 0; }

	char state();

	uint16_t pump_time() { return pump_time_; }

	bool needs_water();

	void set_watered(uint32_t time) { watered_time = time; }

private:
	leading_sensor leading_ = leading_sensor_top;
	uint16_t drylevel_ = 0;
	uint16_t pump_time_ = 0;
	uint32_t loose_time_ = 0;
	uint32_t update_time_ = 0;
	uint32_t watered_time = 0;
	uint16_t top_sensor_ = 0;
	uint16_t bottom_sensor_ = 0;
};

#endif
