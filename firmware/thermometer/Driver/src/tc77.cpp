#include "tc77.h"
#include "gpio.h"

enum tc77_gpio_t
{
	SCK = 0, CS, SIO,
	TC77_GPIO_NUM
};

const gpio_t gpio[TC77_GPIO_NUM] = {
	[SCK] = {GPIOA, GPIO_PIN_5},
	[CS]  = {GPIOA, GPIO_PIN_6},
	[SIO] = {GPIOA, GPIO_PIN_7},
};

TC77::TC77()
{
	GpioInit();
	SpiInit();
}

TC77& TC77::GetInstance()
{
	static TC77 instance;
	return instance;
}

bool TC77::Read(float& temp)
{
	uint8_t data[2];

	gpio_write(gpio[CS], false);
	HAL_SPI_Receive(&hspi, data, 2, 1);
	gpio_write(gpio[CS], true);

	uint16_t temp_int = (data[0] << 5) | (data[1] >> 3);
	bool data_valid = data[1] & 0b00000100;

	temp = temp_int * 0.0625f;

	return !data_valid;
}

void TC77::GpioInit()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = gpio[SCK].pin|gpio[SIO].pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;

	HAL_GPIO_Init(gpio[SCK].port, &GPIO_InitStruct);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = gpio[CS].pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(gpio[CS].port, &GPIO_InitStruct);

	gpio_write(gpio[CS], true);
}

void TC77::SpiInit()
{
	__HAL_RCC_SPI1_CLK_ENABLE();

	hspi.Instance = SPI1;
	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.Direction = SPI_DIRECTION_1LINE;
	hspi.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW; // Inactive: low
	hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi.Init.NSS = SPI_NSS_SOFT;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi.Init.CRCPolynomial = 10;

	HAL_SPI_Init(&hspi);
}
