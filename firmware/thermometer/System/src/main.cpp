#include "System.h"
#include "thermometer.h"

int main(void)
{
	System& sys = System::GetInstance();

	Thermometer::Start();

	sys.OsStart();

	while (1);
}
