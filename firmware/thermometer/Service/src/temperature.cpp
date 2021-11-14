#include "temperature.h"
#include "tc77.h"

const uint32_t AVG_WINDOW_SIZE = 10;
const float NSW = 1.0 / AVG_WINDOW_SIZE; // New sample weight

Temperature::Temperature() : Periodic(100)
{

}

Temperature& Temperature::GetInstance()
{
	static Temperature instance;
	return instance;
}

bool Temperature::Read(float& temp)
{
	temp = this->temp;
	return this->valid;
}

void Temperature::Cyclic()
{
	TC77& thermometer = TC77::GetInstance();
	float current_temp;
	valid = !thermometer.Read(current_temp);

	if(valid) {
		if(has_valid_sample) {
			// Exponential moving average
			temp = (1 - NSW) * temp + NSW * current_temp;
		} else {
			temp = current_temp;
			has_valid_sample = true;
		}
	}
}
