#pragma once

#include "Periodic.h"
#include "Input.h"
#include "Output.h"
#include "button_data.h"
#include "app_state.h"
#include "button_timer.h"

class Thermometer : public Periodic
{
public:
	Thermometer(
		Input<button_state_t> button_left,
		Input<button_state_t> button_right,
		Input<float> temperature,
		Output<float> display,
		Output<bool> alert,
		Output<app_state_t> client_conn
	);

private:
	Input<button_state_t> button_left;
	Input<button_state_t> button_right;
	Input<float> temp_sensor;
	Output<float> display;
	Output<bool> alert;
	Output<app_state_t> client_conn;

	float alert_temp_thr; // Alert temperature threshold

	ButtonTimer timer_left;
	ButtonTimer timer_right;
	int32_t temp_shwitchback_time;

	virtual void PeriodicFunction() override;
};
