#pragma once

#include "config.h"

#ifdef DEBUG_WANTED
#include <HardwareSerial.h>

#define DEBUG(x) Serial.print(x)
#define DEBUGLN(x) Serial.println(x)
#define init_debug() Serial.begin(115200);
#else
#define DEBUG(x) void
#define DEBUGLN(x) void
#define init_debug()
#endif