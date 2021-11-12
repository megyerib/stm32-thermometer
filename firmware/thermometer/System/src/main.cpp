#include <alarm_sound.h>
#include <blinker.h>
#include "System.h"
#include "green_led.h"
#include "seven_seg.h"
#include "display.h"
#include "alarm_sound.h"

int main(void)
{
	System& sys = System::GetInstance();

	GreenLed& led = GreenLed::GetInstance();
	static Blinker blinker(led);
	blinker.Write(true);

	Display& display = Display::GetInstance();
	display.Write(-1000);

	AlarmSound& sound = AlarmSound::GetInstance();
	sound.Write(true);

	sys.OsStart();

	while (1);
}
