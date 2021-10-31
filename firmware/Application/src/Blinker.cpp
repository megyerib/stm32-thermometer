#include "Blinker.h"

void Blinker::Start()
{
	static Blinker instance; // Instantiate only
}

Blinker::Blinker() : Periodic(500)
{
	PortInit();

	state = false;
	Led->Write(false);

	num = -15;
	display->Write(num);
}

void Blinker::Init()
{

}

void Blinker::Cyclic()
{
	state = !state;
	Led->Write(state);

	num++;
	display->Write(num);
}
