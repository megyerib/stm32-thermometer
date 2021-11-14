#include <button_timer.h>

ButtonTimer::ButtonTimer(
	uint32_t period,
	uint32_t until_start,
	uint32_t until_next
) : period(period),
	until_start(until_start),
	until_next(until_next)
{
	time_until_incr_start = until_start;
	time_until_next_incr = until_next;
}

bool ButtonTimer::Increased(const button_state_t& state)
{
	if(state.held_down) {
		if(time_until_incr_start > 0) {
			time_until_incr_start -= period;
		}
	} else {
		time_until_incr_start = until_start;
		time_until_next_incr = until_next;
	}

	if(time_until_incr_start <= 0) {
		time_until_next_incr -= period;
		if(time_until_next_incr <= 0) {
			time_until_next_incr = until_next;
			return true;
		}
	}

	return state.pushed;
}
