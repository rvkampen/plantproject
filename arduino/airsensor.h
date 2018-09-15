#pragma once 

#include "arduino.h"
#include "report.h"

void airsensor_init();
void airsensor_update();
int airsensor_count();
void airsensor_addtoreport(Report & r);

const String humidity_formatted();
const String temperature_formatted();
