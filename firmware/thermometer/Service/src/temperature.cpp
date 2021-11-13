#include "temperature.h"
#include "tc77.h"

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
	valid = thermometer.Read(temp);
	// Averaging etc. goes here
}
