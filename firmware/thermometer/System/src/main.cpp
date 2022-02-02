#include <buzzer.h>
#include "System.h"
#include "thermometer.h"
#include "FreeRtosTask.h"

#include "debouncer.h"
#include "seven_seg.h"
#include "buzzer.h"
#include "nucleo_uart.h"
#include "button.h"

int main(void)
{
	System& sys = System::GetInstance();

	// Buttons
	Debouncer& debouncer = Debouncer::GetInstance();
	FreeRtosTask debouncer_task(debouncer);
	Button& left_button = Button::GetInstance(LEFT);
	Button& right_button = Button::GetInstance(RIGHT);

	// Display
	SevenSeg& seven_seg = SevenSeg::GetInstance();
	FreeRtosTask seven_seg_task(seven_seg);


	// Buzzer
	Buzzer& buzzer = Buzzer::GetInstance();
	FreeRtosTask buzzer_task(buzzer);

	// Client connection
	NucleoUart& uart = NucleoUart::GetInstance();

	// Application


	sys.OsStart();

	while (1);
}
