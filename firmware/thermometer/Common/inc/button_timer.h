#pragma once

#include "button_data.h"

class ButtonTimer
{
public:
	ButtonTimer(uint32_t period, uint32_t until_start, uint32_t until_next);
	bool Increased(const button_state_t& state);

private:
	const uint32_t period;
	const uint32_t until_start;
	const uint32_t until_next;

	int32_t time_until_incr_start;
	int32_t time_until_next_incr;
};
