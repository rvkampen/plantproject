#include "Time.h"
#include "config.h"
#include <Arduino.h>

uint32_t last_time = 0;
uint16_t last_millis = 0;

void setTime(uint32_t timestamp)
{
    last_millis = millis();
    last_time = timestamp;
}

uint32_t getTime()
{
    uint16_t actual = millis();
    uint16_t delay = actual - last_millis;
    uint32_t time = last_time + (delay / 1000);
    if (actual < last_millis)
    {
        //overflow, so update to get the right time next time as well
        last_millis = actual;
        last_time = time;
    }
    return time;
}

bool isWaterWindow()
{
    uint32_t daytime = getTime() % (24 * 60 * 60);
    return daytime > WATERWINDOW_START && daytime < WATERWINDOW_END;
}
