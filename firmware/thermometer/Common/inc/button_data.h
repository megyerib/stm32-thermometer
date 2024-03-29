#pragma once

#include "gpio.h"

enum button_t
{
	LEFT,
	RIGHT,
	BUTTON_NUM
};

const gpio_t button_gpio[BUTTON_NUM] = {
	[LEFT]  = {GPIOC, GPIO_PIN_0},
	[RIGHT] = {GPIOC, GPIO_PIN_1},
};

struct button_state_t
{
	bool pushed;    // A rising edge was detected after the last reading
	bool held_down; // A button is currently held down
};
