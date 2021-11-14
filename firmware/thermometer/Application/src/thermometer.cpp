#include "thermometer.h"
#include "display.h"
#include "temperature.h"
#include "button.h"
#include "alarm_sound.h"
#include "nucleo_uart.h"

const uint32_t PERIOD_ms = 20;
const uint32_t DOWNHOLD_THRESHOLD_ms = 500; // Hold down button for this much ms to start increasing threshold
const uint32_t SWITCH_BACK_TIME_ms = 1000;
const uint32_t THR_INCR_PERIOD_ms = 100; // Threshold increase period while holding down button
const float DEFAULT_ALERT_THRESHOLD = 30.0f;

Thermometer::Thermometer() : Periodic(PERIOD_ms),
		                     timer_left(PERIOD_ms, DOWNHOLD_THRESHOLD_ms, THR_INCR_PERIOD_ms),
							 timer_right(PERIOD_ms, DOWNHOLD_THRESHOLD_ms, THR_INCR_PERIOD_ms),
							 client_conn(NucleoUart::GetInstance())
{
	alert_temp_thr = DEFAULT_ALERT_THRESHOLD;
	temp_shwitchback_time = 0;

	AlarmSound::GetInstance(); // Init
}

void Thermometer::Start()
{
	static Thermometer instance;
}

void Thermometer::Cyclic()
{
	Temperature& temp = Temperature::GetInstance();

	float temperature = 0;
	temp.Read(temperature);

	button_state_t left_button;
	button_state_t right_button;

	Button::GetInstance(LEFT).Read(left_button);
	Button::GetInstance(RIGHT).Read(right_button);

	bool decrease = timer_left.Increased(left_button);
	bool increase = timer_right.Increased(right_button);

	if(increase || decrease) {
		alert_temp_thr += (int)(increase - decrease) * 0.1f;
		temp_shwitchback_time = SWITCH_BACK_TIME_ms;
	}

	if(temp_shwitchback_time <= 0) {
		Display::GetInstance().Write(temperature);
	} else {
		Display::GetInstance().Write(alert_temp_thr);
		temp_shwitchback_time -= PERIOD_ms;
	}

	bool alert = temperature > (alert_temp_thr - 0.001f);
	AlarmSound::GetInstance().Write(alert);

	app_state_t state = {
		.temperature = temperature,
		.threshold   = alert_temp_thr
	};

	client_conn.Write(state);
}
