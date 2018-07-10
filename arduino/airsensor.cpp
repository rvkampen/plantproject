#include "airsensor.h"
#include "pinout.h"

#include <Wire.h>
#include <DHT.h>

// DHT11 5v: one wire -> Arduino Digital 5
DHT environment_sensor(AIRSENSOR_PIN, DHT11);

String humidity_, temperature_;

void airsensor_update() {
	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float humidity = environment_sensor.readHumidity();
	float temperature = environment_sensor.readTemperature(false);

	humidity_ = isnan(humidity) ? "--" : String(humidity, 0);
	temperature_ = isnan(temperature) ? "--" : String(temperature, 0);
	/*if (!isnan(humidity) && !isnan(temperature))
	{
	// Compute heat index in Celsius (isFahreheit = false)
	// float hic = dht.computeHeatIndex(t, h, false);
	}*/

}

const String & humidity_formatted()
{
	return humidity_;
}

const String & temperature_formatted()
{
	return temperature_;
}
