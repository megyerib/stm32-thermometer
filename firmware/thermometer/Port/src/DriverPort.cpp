#include "BuzzerService.h"
#include "Buzzer.h"
#include "Display7Seg.h"
#include "DisplayService.h"

void BuzzerService::PortInit()
{
	Buzzer = Buzzer::GetInstance();
}

void DisplayService::PortInit()
{
	for (int i = 0; i < 3; i++)
	{
		digit[i] = Display7Seg::GetInstance(i);
	}
}
