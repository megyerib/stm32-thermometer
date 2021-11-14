#include "button.h"
#include "debouncer.h"

bool Button::Read(button_state_t& state)
{
	Debouncer& debouncer = Debouncer::GetInstance();
	uint16_t gpio_pin = button_gpio[button].pin;

	state.pushed = debouncer.GetRisingEdge(gpio_pin);
	state.held_down = debouncer.GetValue(gpio_pin);

	return false;
}

Button& Button::GetInstance(button_t button)
{
	static Button instances[BUTTON_NUM] = {
		[LEFT]  = Button(LEFT),
		[RIGHT] = Button(RIGHT),
	};

	return instances[button];
}

Button::Button(button_t button) : button(button)
{
	Debouncer::GetInstance(); // init
}
