#pragma once

#include "config.h"

#ifdef DEBUG_WANTED
#include <HardwareSerial.h>
#include <Arduino.h>

class debug_time {
public:
    debug_time(char* name)
        :name(name)
        ,start(millis())
    {

    }
    ~debug_time()
    {
        uint16_t duration = millis() - start;
        Serial.print(name);
        Serial.print(" took ");
        Serial.print(duration / 1000.0);
        Serial.println(" sec");
    }
private:
    uint16_t start;
    char* name;
};
#define DEBUG_TRACKTIME debug_time func_timer(__FUNCTION__);

#define DEBUG(x) Serial.print(x)
#define DEBUGLN(x) Serial.println(x)
#define init_debug DEBUG_TRACKTIME Serial.begin(DEBUG_SERIALSPEED);
#else
#define DEBUG(x) void
#define DEBUGLN(x) void
#define init_debug
#define DEBUG_TRACKTIME
#endif