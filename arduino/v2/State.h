#pragma once

#define SETUP_ID 2                 // Number of this setup on the website
#define SENSOR_COUNT 5             // Room sensor number
#define ITEM_COUNT 16              // Plant or bucket
#define WATERWINDOW_START 8 * 3600 // Start time watering is allowed
#define WATERWINDOW_END   9 * 3600 // End time watering is allowed

#include <stdint.h>

struct sensor
{
    int32_t value;                 // In 0.01 units
};

struct item
{
    bool isBucket = false;         // s 
    bool isPlant = false;          // s 
    bool isEnabled = false;        // s 
    bool looseWarning = false;     // s*  // If water has not reached plant in pumpTime
    bool wateredInLastGo = false;  //  
    bool isUpdated = false;        // s 
    
    // config
    int16_t lowWaterLevel = 0;     // s // Minimum value for water sensor
    int8_t parentBucket = 0xFF;    // s // Default to 0xFF because 0 is a valid adress
    int16_t pumpTime = 0;          // s // Time allowed to pump before water must reach the plant, otherwise it might leak in milliseconds
    int16_t fillTime = 0;          // s // Time that water should be flowing to plant, rough indication of amount of water given in milliseconds

    // state
    int16_t actualPumpTime = 0;    //  // Last time needed to pump to plant
    int16_t actualWaterLevel = 0;  //  // Last value for water sensor
    int16_t actualTemperature = 0; //  // Last value for temperature sensor, in .01 degrees celcius

    void setLoose();
    void setEnabledFromServer(bool enabled);
};

struct state
{
    bool successPostedEnabled = true;
    bool hasWateredInLastWindow = false;
    
    // the adress is the index in this array
    sensor Sensors[SENSOR_COUNT];
    item Items[ITEM_COUNT];

    void StartUpdate();

    void ProcessTimestamp(uint32_t ts);

    void ProcessBucket(long id, long lowlevel);

    void ProcessPlant(long id, long lowlevel, bool enabled, long bucketid, long pumptime, long filltime);

    void Cancel() {
    }

    void Confirm();
};

extern state State;

