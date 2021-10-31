#include "GreenLed.h"
#include "stm32f4xx_hal.h"

int32_t GreenLed::Write(const bool& data)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, data ? GPIO_PIN_SET : GPIO_PIN_RESET);

	return OUTPUT_WRITE_OK;
}

GreenLed* GreenLed::GetInstance()
{
	static GreenLed instance;
	return &instance;
}

GreenLed::GreenLed()
{
	Init();
}

void GreenLed::Init()
{
	// Green LED: PA5

	GPIO_InitTypeDef GpioStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GpioStruct.Pin   = GPIO_PIN_5;
	GpioStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GpioStruct.Pull  = GPIO_NOPULL;
	GpioStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOA, &GpioStruct);
}
