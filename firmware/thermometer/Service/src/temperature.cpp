#include "temperature.h"

const uint32_t WINDOW_SIZE = 10; // Avveraging window size
const float NSW = 1.0 / WINDOW_SIZE; // New sample weight

Temperature::Temperature(Input<float>& sensor) : Periodic(100),
                                                 sensor(sensor)
{

}

Temperature& Temperature::GetInstance()
{
	static Temperature instance;
	return instance;
}

bool Temperature::Read(float& temp)
{
	temp = this->temperature;
	return this->valid;
}

void Temperature::PeriodicFunction()
{
	float current_temp;
	valid = !sensor.Read(current_temp);

	if(valid) {
		if(has_valid_sample) {
			// Exponential moving average
			temperature = (1 - NSW) * temperature + NSW * current_temp;
		} else {
			temperature = current_temp;
			has_valid_sample = true;
		}
	}
}
