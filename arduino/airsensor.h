#pragma once 

#include "Arduino.h"

class Report;

void airsensor_init();
void airsensor_update();
int  airsensor_count();
void airsensor_addtoreport(Report & r);

const String airsensor_display();
