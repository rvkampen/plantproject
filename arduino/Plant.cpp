#include "Plant.h"
#include "Time.h"

Plant::Plant(uint16_t humidity_when_dry, uint16_t pump_time)
	: humidity_when_dry_(humidity_when_dry)
	, pump_time_(pump_time)
{
}

void Plant::update(uint32_t update_time, uint16_t humidity)
{
	update_time_ = update_time;
	humidity_sensor_ = humidity;
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
		return 'S';
	auto days = time_day_diff(watered_time);
	if (days == 0)
		return 'W';
	if (days > 9)
		return '*';
	return '0' + days;
}

bool Plant::needs_water()
{
	return humidity_sensor_ < humidity_when_dry_;
}

char Plant::get_state_update(uint32_t time)
{
	if (is_loose())
		return 'L';
	if(watered_time == 0)
		return 'S';
	if(time == watered_time)
		return 'W';
	if(needs_water())
		return 'D';
}
