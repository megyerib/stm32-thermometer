#pragma once

#include <button_timer.h>
#include "Periodic.h"
#include "client_connection.h"

class Thermometer : public Periodic
{
public:
	static void Start();

private:
	float alert_temp_thr; // Alert temperature threshold

	ButtonTimer timer_left;
	ButtonTimer timer_right;
	int32_t temp_shwitchback_time;

	ClientConnection client_conn;

	Thermometer();
	virtual void Cyclic() override;
};
