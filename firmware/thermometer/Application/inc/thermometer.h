#pragma once

#include <button_timer.h>
#include "Periodic.h"

class Thermometer : public Periodic
{
public:
	static void Start();

private:
	float alert_temp_thr; // Alert temperature threshold

	ButtonTimer timer_left;
	ButtonTimer timer_right;
	int32_t temp_shwitchback_time;

	Thermometer();
	virtual void Cyclic() override;
};
