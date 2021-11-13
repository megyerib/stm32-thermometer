#include "seven_seg.h"
#include "gpio.h"
#include "stm32f4xx_hal.h"

enum display_gpio_t {
	A = 0, B, C, D, E, F, G, P,
	COM0, COM1, COM2,
	CLK, EN,
	DISPLAY_GPIO_NUM
};

const gpio_t display_gpio[DISPLAY_GPIO_NUM] = {
	[A]    = {GPIOA, GPIO_PIN_10},
	[B]    = {GPIOB, GPIO_PIN_3},
	[C]    = {GPIOB, GPIO_PIN_5},
	[D]    = {GPIOB, GPIO_PIN_10},
	[E]    = {GPIOA, GPIO_PIN_8},
	[F]    = {GPIOA, GPIO_PIN_9},
	[G]    = {GPIOC, GPIO_PIN_7},
	[P]    = {GPIOB, GPIO_PIN_4},

	[COM0] = {GPIOB, GPIO_PIN_9},
	[COM1] = {GPIOB, GPIO_PIN_8},
	[COM2] = {GPIOC, GPIO_PIN_9},

	[CLK]  = {GPIOC, GPIO_PIN_4},
	[EN]   = {GPIOB, GPIO_PIN_6},
};

const gpio_t display_com_gpio[3] = {
	[0] = display_gpio[COM0],
	[1] = display_gpio[COM1],
	[2] = display_gpio[COM2],
};

SevenSeg::SevenSeg() : Periodic(1)
{
	// GPIO Ports Clock Enable
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// Configure GPIO pins
	for(int i = 0; i < DISPLAY_GPIO_NUM; i++) {
		GPIO_InitTypeDef GPIO_InitStruct;

		GPIO_InitStruct.Pin   = display_gpio[i].pin;
		GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull  = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

		HAL_GPIO_Init(display_gpio[i].port, &GPIO_InitStruct);

		gpio_write(display_gpio[i], false);
	}

	gpio_write(display_gpio[CLK], true); // CLK is low active
}

SevenSeg& SevenSeg::GetInstance()
{
	static SevenSeg instance;
	return instance;
}

bool SevenSeg::Write(const digit_t (&input)[3])
{
	digit[0] = input[0];
	digit[1] = input[1];
	digit[2] = input[2];
	return false;
}

void SevenSeg::Cyclic()
{
	static int activeDigit = 0;

	LightUpDigit(activeDigit, digit[activeDigit]);

	activeDigit++;
	activeDigit %= DIGIT_NUM;
}

void SevenSeg::LightUpDigit(int num, digit_t value)
{
	num = num % DIGIT_NUM;

	// Segment
	for(int i = 0; i < 8; i++) {
		bool gpio_val = value & (1 << (7 - i));
		gpio_write(display_gpio[i],	gpio_val);
	}

	// Common reset
	int prevnum = (num + 2) % 3;
	gpio_write(display_com_gpio[prevnum], false);

	// Tickle the D flip flops' clock input
	gpio_write(display_gpio[CLK], false);
	gpio_write(display_gpio[CLK], true);

	// Common set
	gpio_write(display_com_gpio[num], true);
}
