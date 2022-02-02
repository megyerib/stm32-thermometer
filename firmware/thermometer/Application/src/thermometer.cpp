#include "thermometer.h"

const uint32_t PERIOD_ms             = 20;
const uint32_t DOWNHOLD_THRESHOLD_ms = 500; // Hold down button for this much ms to start increasing threshold
const uint32_t SWITCH_BACK_TIME_ms   = 1000;
const uint32_t THR_INCR_PERIOD_ms    = 100; // Threshold increase period while holding down button
const float DEFAULT_ALERT_THRESHOLD  = 30.0f;

Thermometer::Thermometer(
	Input<button_state_t> button_left,
	Input<button_state_t> button_right,
	Input<float> temp_sensor,
	Output<float> display,
	Output<bool> alert,
	Output<app_state_t> client_conn
) :
	Periodic(PERIOD_ms),
	timer_left(PERIOD_ms, DOWNHOLD_THRESHOLD_ms, THR_INCR_PERIOD_ms),
	timer_right(PERIOD_ms, DOWNHOLD_THRESHOLD_ms, THR_INCR_PERIOD_ms),
	client_conn(NucleoUart::GetInstance()),

	button_left(button_left),
	button_right(button_right),
	temp_sensor(temp_sensor),
	display(display),
	alert(alert),
	client_conn(client_conn)
{
	alert_temp_thr = DEFAULT_ALERT_THRESHOLD;
	temp_shwitchback_time = 0;
}

void Thermometer::PeriodicFunction()
{
	float temperature = 0;
	button_state_t left_button;
	button_state_t right_button;

	temp_sensor.Read(temperature);
	button_left.Read(left_button);
	button_right.Read(right_button);

	bool decrease = timer_left.Increased(left_button);
	bool increase = timer_right.Increased(right_button);

	if(increase || decrease) {
		alert_temp_thr += (int)(increase - decrease) * 0.1f;
		temp_shwitchback_time = SWITCH_BACK_TIME_ms;
	}

	if(temp_shwitchback_time <= 0) {
		display.Write(temperature);
	} else {
		display.Write(alert_temp_thr);
		temp_shwitchback_time -= PERIOD_ms;
	}

	bool alert_on = temperature > (alert_temp_thr - 0.001f);
	alert.Write(alert_on);

	app_state_t state = {
		.temperature = temperature,
		.threshold   = alert_temp_thr
	};

	client_conn.Write(state);
}
