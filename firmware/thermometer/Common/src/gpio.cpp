#include "gpio.h"

void gpio_write(const gpio_t& gpio, bool value)
{
	HAL_GPIO_WritePin(
		gpio.port,
		gpio.pin,
		value ? GPIO_PIN_SET : GPIO_PIN_RESET
	);
}

bool gpio_read(const gpio_t& gpio)
{
	GPIO_PinState res = HAL_GPIO_ReadPin(
		gpio.port,
		gpio.pin
	);

	return res == GPIO_PIN_SET;
}
