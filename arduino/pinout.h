// pinout.h

#ifndef _PINOUT_h
#define _PINOUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//------------PIN SETUP----------------------
// analog
#define SENSOR_TOP_PIN 		0
#define SENSOR_TOP_PINA		PIN_A0
#define SENSOR_BOTTOM_PIN	1
#define SENSOR_BOTTOM_PINA	PIN_A1
// pin 4 & 5 are used for I2C

//digital
// 0 & 1 are used for serial communication
#define CLOCK_RST_PIN		2
#define CLOCK_DAT_PIN		3
#define CLOCK_CLK_PIN		4
#define AIRSENSOR_PIN		5
#define PIEZO_PIN 			6
#define SELECT_PIN0 		7
#define SELECT_PIN1 		8
#define SELECT_PIN2 		9
#define SELECT_PIN3 		10
#define SENSOR_ENABLE_PIN 	11
#define PUMP_PIN 			12
#define WATERFLOW_PIN 		13

void pin_init();

#endif

