#include "thermometer.h"
#include "display.h"
#include "temperature.h"

Thermometer::Thermometer() : Periodic(500)
{

}

void Thermometer::Start()
{
	static Thermometer instance;
}

void Thermometer::Cyclic()
{
	Display& disp = Display::GetInstance();
	Temperature& temp = Temperature::GetInstance();

	float temperature = 0;
	temp.Read(temperature);

	disp.Write(temperature);
}
