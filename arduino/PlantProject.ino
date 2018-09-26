//#include "pinout.h"
#include "Report2.h"
#include "time.h"
#include "airsensor.h"
//#include "LCD.h"
//#include "Plant.h"
#include "HTTPPost.h"
#include "NTP.h"

/*
//--------------PARAMETERS-----------------
Plant plants_[] = { 
	Plant(leading_sensor_top, 512, 5000),
};

constexpr auto START_HOUR = 8;
constexpr auto START_MINUTE = 0;
constexpr auto END_HOUR = 9;
constexpr auto END_MINUTE = 0;
constexpr auto MAX_TIMEOUT = 10000;

// the bucket is like a normal plant and has also two sensors (top = warning level, bottom = error level)
constexpr auto BUCKET_SENSOR = 15;
//-----------------------------------------

enum state
{
	update_environment,
	evaluate_bucket,
	iterate,
	measure_plant,
	water_plant_start,
	water_plant_pump_started,
	water_plant_pumping,
	send_report,
	waiting,
};

enum errorstate : byte
{
	ok = 0x00,
	no_time = 0x01,
	no_water = 0x02,
};

state state_ = update_environment;
errorstate errorstate_ = ok;
bool watering_allowed_ = true;
uint32_t last_water_day_ = 0;
uint16_t bucket_sensor_empty_ = 0;
uint16_t bucket_sensor_low_ = 0;
byte plant_counter_ = 0;
unsigned long pump_started_ = 0;
unsigned long pump_effective_ = 0;
unsigned long last_run_ = 0;
bool filter_watering_time_ = true;

#define plant_count sizeof(plants_)/sizeof(Plant)

bool is_watering_allowed(bool use_time)
{
	if (use_time
		&& (time_before(START_HOUR, START_MINUTE)
			|| !time_before(END_HOUR, END_MINUTE)))
		return false;

	return errorstate_ == ok
		&& time_day()!=last_water_day_;
}

void select_output(byte plant)
{
	digitalWrite(SELECT_PIN0, plant & 0x01);
	digitalWrite(SELECT_PIN1, plant & 0x02);
	digitalWrite(SELECT_PIN2, plant & 0x04);
	digitalWrite(SELECT_PIN3, plant & 0x08);
}

void read_sensors(uint16_t & top_sensor, uint16_t & bottom_sensor)
{
	digitalWrite(SENSOR_ENABLE_PIN, HIGH);
	delay(10);
	top_sensor = analogRead(SENSOR_TOP_PIN);
	bottom_sensor = analogRead(SENSOR_BOTTOM_PIN);
	digitalWrite(SENSOR_ENABLE_PIN, LOW);
}

void enable_pump()
{
	digitalWrite(PUMP_PIN, HIGH);
}

void disable_pump()
{
	digitalWrite(PUMP_PIN, LOW);
}

bool is_water_at_hose_end()
{
	return digitalRead(WATERFLOW_PIN);
}

bool check_timeout(unsigned long now, unsigned long past, unsigned long timeout)
{
	auto duration = now - past; // overflow is covered by unsigned substraction
	return duration > timeout;
}

void update_plant_sensors()
{
	uint16_t  top_sensor, bottom_sensor;
	read_sensors(top_sensor, bottom_sensor);
	plants_[plant_counter_].update(time_unixtimestamp(), top_sensor, bottom_sensor);
}*/

void setup()
{
	Serial.begin(115200);
	Serial.println(F("Starting..."));
	network_init();
	airsensor_init();
	ntp_init();
	time_init(ntp_request_time_safe());

	//lcd_init();
	//pin_init();
	Serial.println(F("Startup done!"));
}

void loop()
{
	time_update();
	airsensor_update();
	//lcd_update_top("--:--", humidity_formatted(), temperature_formatted());

	byte sensor_count = airsensor_count() + 1;
	String json;
	json.reserve(Report::max_length(sensor_count));
	{
		// let our report go out of scope as soon as we have a report ready
		Report r(time_unixtimestamp(), sensor_count);

		airsensor_addtoreport(r);

		if (time_clock_temperature() > 1) // only send it when its valid
			r.add(clock_temperature, time_clock_temperature());

		r.printTo(json);
	}

	Serial.println(json);

	char serverName[] = "www.plantproject.dx.am";
	char pageName[] = "/update.php";
	http_post(serverName, 80, pageName, json);

	delay(30000);
}
/*
void loop()
{
	switch (state_)
	{
	case update_environment:
		time_update();
		airsensor_update();
		lcd_update_top(time_formatted(), humidity_formatted(), temperature_formatted());
		if (check_timeout(time_unixtimestamp(), last_run_, 30 * 60))
		{
			bool firstrun = last_run_ == 0;
			last_run_ = time_unixtimestamp();
			errorstate_ = time_ok() ? ok : no_time;
			watering_allowed_ = is_watering_allowed(filter_watering_time_);
			state_ = evaluate_bucket;
			plant_counter_ = 0;

			if (firstrun)
			{
				watering_allowed_ = false;
				last_run_ -= (25 * 60);
				filter_watering_time_ = false;
			}
			else
				filter_watering_time_ = true;
		}
		else
			delay(100);
		break;
	case evaluate_bucket:
		select_output(BUCKET_SENSOR);
		read_sensors(bucket_sensor_empty_, bucket_sensor_low_);
		if (bucket_sensor_low_ < 512) 
		{
			lcd_update_state(BUCKET_SENSOR, bucket_sensor_empty_ < 512 ?'!':'F');
			errorstate_ |= no_water;
			if(watering_allowed_)
				tone(PIEZO_PIN, 500, 300); // frequency Hz, duration ms
		}
		else
			lcd_update_state(BUCKET_SENSOR, bucket_sensor_empty_ < 512 ? 'W' : '^');
		if (watering_allowed_ && errorstate_ == ok)
			last_water_day_ = time_day();
		state_ = iterate;
		break;
	case iterate:
		if (plant_counter_ < plant_count)
			state_ = measure_plant;
		else
			state_ = send_report;
		break;
	case measure_plant:
		select_output(plant_counter_);
		update_plant_sensors();
		lcd_update_state(plant_counter_, plants_[plant_counter_].state());
		if (watering_allowed_ 
			&& errorstate_ == ok
			&& plants_[plant_counter_].needs_water() 
			&& plants_[plant_counter_].is_loose())
			state_ = water_plant_start;
		else
		{
			plant_counter_++;
			state_ = iterate;
		}
		break;
	case water_plant_start:
		enable_pump();
		pump_started_ = millis();
		state_ = water_plant_pump_started;
		lcd_update_state(plant_counter_, '>');
		break;
	case water_plant_pump_started:
	{
		auto max = pump_started_ + MAX_TIMEOUT;
		if (is_water_at_hose_end())
		{
			state_ = water_plant_pumping;
			pump_effective_ = millis();
			lcd_update_state(plant_counter_, 'P');
		}
		else if (check_timeout(millis(), pump_started_, MAX_TIMEOUT))
		{
			disable_pump();
			plants_[plant_counter_].set_loose(time_unixtimestamp());
			lcd_update_state(plant_counter_, plants_[plant_counter_].state());
			plant_counter_++;
			state_ = evaluate_bucket;
		}
	}
	break;
	case water_plant_pumping:
		if (check_timeout(millis(), pump_effective_, plants_[plant_counter_].pump_time()))
		{
			lcd_update_state(plant_counter_, plants_[plant_counter_].state());
			plant_counter_++;
			state_ = evaluate_bucket;
			plants_[plant_counter_].set_watered(time_unixtimestamp());
		}
		break;
	case send_report:
		{
			String json = F("data=");
			json.reserve(230);
			{
				// let our report go out of scope as soon as we have a report ready
				Report r(time_unixtimestamp(), airsensor_count() + 1);

				airsensor_addtoreport(r);
				if (time_clock_temperature() > 1)
					r.add(clock_temperature, time_clock_temperature());
				r.printTo(json);
			}

			Serial.println(json);

			char serverName[] = "www.plantproject.dx.am";
			char pageName[] = "/update.php";
			http_post(serverName, 80, pageName, json);

			state_ = update_environment;
		}
		break;
	default:
		break;
	}
}
*/