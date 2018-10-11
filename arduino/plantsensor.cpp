#include "plantsensor.h"
#include <OneWire.h> 
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

struct tempsensor
{
	uint8_t address[8];
	float value;
};
tempsensor sensors_[16];
uint8_t sensor_count_;

void plantsensor_init()
{
	sensors.begin();
	sensors.setResolution(12);
}

void plantsensor_update()
{
	Serial.print(F("Requesting temperatures..."));
	sensors.requestTemperatures(); // Send the command to get temperature readings 
	Serial.println(F("DONE"));

	Serial.print(F("Reading temperatures... "));
	for (sensor_count_ = 0; sensors.getAddress(&sensors_[sensor_count_].address[0], sensor_count_); sensor_count_++)
	{
		sensors_[sensor_count_].value = sensors.getTempC(&sensors_[sensor_count_].address[0]);
	}
	Serial.print(sensor_count_);
	Serial.println(F(" Found!"));


	//Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"?  
	  // You can have more than one DS18B20 on the same bus.  
	  // 0 refers to the first IC on the wire 

}

uint8_t plantsensor_count()
{
	return sensor_count_;
}

void plantsensor_addtoreport(Report & r)
{
}

const String plantsensor_formatted(uint8_t index)
{
	return String(sensors_[index].value,4);
}
