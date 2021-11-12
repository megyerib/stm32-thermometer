#include <blinker.h>

Blinker::Blinker(Output<bool>& led) : Periodic(500),
		                              led(led)
{
	led.Write(false);
}

bool Blinker::Write(const bool& on)
{
	enabled = on;
	state = enabled;
	led.Write(state);
	return false;
}

void Blinker::Cyclic()
{
	if (enabled) {
		state = !state;
		led.Write(state);
	}
}
