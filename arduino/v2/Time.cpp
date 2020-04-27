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
    uint16_t delay = millis() - last_millis;
    return last_time + (delay/1000);
}

bool isWaterWindow()
{
    uint32_t daytime = getTime() % (24 * 60 * 60);
    return daytime > WATERWINDOW_START && daytime < WATERWINDOW_END;
}
