#include "Blinker.h"
#include "GreenLed.h"
#include "DisplayService.h"

void Blinker::PortInit()
{
	Led     = GreenLed       :: GetInstance();
	display = DisplayService :: GetInstance();
}
