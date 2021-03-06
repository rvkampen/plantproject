#pragma once

// common
#define DEBUG_WANTED
#define DEBUG_SERIALSPEED 115200

// nerwork
#define MAC             0XDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEB 
#define SERVERADDRESS   ""
#define SERVERPORT      80

// setup
#define SETUP_ID "2"               // Number of this setup on the website
#define SENSOR_COUNT 0             // Ambient room sensor count (todo not yet implemented fully)
#define ITEM_COUNT 16              // Total plant or bucket count
#define WATERWINDOW_START 8 * 3600 // Start time watering is allowed (seconds since midnight)
#define WATERWINDOW_END   9 * 3600 // End time watering is allowed   (seconds since midnight)
