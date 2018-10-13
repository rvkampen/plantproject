#include "Configuration.h"

// +- 630 = completely dry
// +- 320 = completely wet
Plant plants_[] = {
	Plant(500, 5000),
	Plant(500, 5000),
	Plant(500, 5000),
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