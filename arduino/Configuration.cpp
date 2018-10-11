#include "Configuration.h"

Plant plants_[] = {
	Plant(leading_sensor_top, 512, 5000),
	// add plants (maximum is 15)
};

static_assert(sizeof(plants_) / sizeof(Plant) <= 15, "Too much plants defined");

// ----------------------------------------
Plant & get_plant(byte index)
{
	return plants_[index];
}
byte get_plant_count()
{
	return sizeof(plants_) / sizeof(Plant);
}