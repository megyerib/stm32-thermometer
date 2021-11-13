#pragma once

#include "stm32f4xx_hal.h"

struct gpio_t {
	GPIO_TypeDef* port;
	uint16_t      pin;
};

void gpio_write(const gpio_t& gpio, bool value);

bool gpio_read(const gpio_t& gpio);
