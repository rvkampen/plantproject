#pragma once 

#include "arduino.h"

void network_init();

bool http_post(char * domainBuffer, int remoteport, char * page, const String & data);
