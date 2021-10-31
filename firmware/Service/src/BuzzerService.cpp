#include "BuzzerService.h"

void BuzzerService::Start()
{
	static BuzzerService instance; // Instantiate only
}

BuzzerService::BuzzerService() : Periodic(500)
{
	PortInit();

	state = false;
}

void BuzzerService::Init()
{

}

void BuzzerService::Cyclic()
{
	state = !state;

	const SquareWave on  = {440.0f, 0.5f};
	const SquareWave off = {440.0f, 0.0f};

	if (state == true)
	{
		Buzzer->Write(on);
	}
	else
	{
		Buzzer->Write(off);
	}
}
