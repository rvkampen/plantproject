#pragma once

#include "arduino.h"

void ntp_init();

uint32_t ntp_request_time_safe();
