#pragma once

#include "arduino.h"
#include "Report2.h"

void plantsensor_init();
void plantsensor_update();
uint8_t plantsensor_count();
void plantsensor_addtoreport(Report & r);

const String plantsensor_formatted(uint8_t index);
