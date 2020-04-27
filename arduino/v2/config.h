#pragma once

// common
#define DEBUG_WANTED

// nerwork
#define MAC             0XDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEB 
#define SERVERADDRESS   ""
#define SERVERPORT      80

// setup
#define SETUP_ID "2"               // Number of this setup on the website
#define SENSOR_COUNT 5             // Room sensor number
#define ITEM_COUNT 16              // Plant or bucket
#define WATERWINDOW_START 8 * 3600 // Start time watering is allowed (seconds since midnight)
#define WATERWINDOW_END   9 * 3600 // End time watering is allowed   (seconds since midnight)
