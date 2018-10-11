#include "Plant.h"
#include "Time.h"

Plant::Plant(leading_sensor l, uint16_t drylevel, uint16_t pump_time)
	: leading_(l)
	, drylevel_(drylevel)
	, pump_time_(pump_time)
{
}

void Plant::update(uint32_t update_time, uint16_t top_sensor, uint16_t bottom_sensor)
{
	update_time_ = update_time;
	top_sensor_ = top_sensor;
	bottom_sensor_ = bottom_sensor;
}

char Plant::state()
{
	if (is_loose()) {
		if (time_day_diff(loose_time_) == 0)
			return 'L';
		else
			return '!';
	}
	if (needs_water())
	{
		if (time_day_diff(watered_time) == 0)
			return 'T';
		else
			return 'D';
	}
	if (watered_time == 0)
		return '0';
	auto days = time_day_diff(watered_time);
	if (days == 0)
		return 'W';
	if (days > 9)
		return '*';
	return '0' + days;
}

 bool Plant::needs_water()
{
	int val = 1024;
	switch (leading_)
	{
	case leading_sensor_top: val = top_sensor_; break;
	case leading_sensor_bottom: val = bottom_sensor_; break;
	case leading_sensor_average: val = (top_sensor_ + bottom_sensor_) / 2; break;
	}
	return val < drylevel_;
}
