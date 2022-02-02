#include "debouncer.h"
#include "stm32f4xx_hal.h"
#include "button_data.h"

Debouncer& Debouncer::GetInstance()
{
	static Debouncer instance;
	return instance;
}

bool Debouncer::GetValue(uint16_t mask)
{
	return (filteredValue & mask) != 0;
}

bool Debouncer::GetRisingEdge(uint16_t mask)
{
	bool ret = (risingEdges & mask) != 0;
	risingEdges &= ~mask; // Clear edge
	return ret;
}

void Debouncer::PeriodicFunction()
{
	uint32_t prevFiltered = filteredValue;

	// Set index
	i_meas++;
	i_meas %= DEBOUNCING_WINDOW_SIZE;

	// Read
	meas[i_meas] = gpio_port->IDR;

	// Filter
	uint32_t zeros = 0x00000000;
	uint32_t ones  = 0xFFFFFFFF;

	for (int i = 0; i < DEBOUNCING_WINDOW_SIZE; i++)
	{
		zeros |= meas[i];
		ones  &= meas[i];
	}

	filteredValue &= zeros;
	filteredValue |= ones;

	// Detect rising edge
	uint32_t newEdge = (~prevFiltered) & filteredValue;
	risingEdges |= newEdge;
}

Debouncer::Debouncer() : Periodic(1)
{
	gpio_port = button_gpio[LEFT].port;

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitStruct.Pin   = button_gpio[LEFT].pin | button_gpio[RIGHT].pin;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(gpio_port, &GPIO_InitStruct);
}

void Debouncer::ClearRisingEdges()
{
    risingEdges = 0;
}
