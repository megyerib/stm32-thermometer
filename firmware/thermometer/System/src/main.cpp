#include "Blinker.h"
#include "BuzzerService.h"
#include "System.h"

int main(void)
{
	System* sys = System::GetInstance();
	Blinker::Start();
	//BuzzerService::Start();

	sys->OsStart();

	while (1);
}
