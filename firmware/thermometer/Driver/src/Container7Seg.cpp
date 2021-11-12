#include "Container7Seg.h"
#include "Pinout7Seg.h"

// TODO NAMING!!!

Container7Seg* Container7Seg::GetInstance()
{
	static Container7Seg instance;
	return &instance;
}

Container7Seg::Container7Seg() : Periodic(1)
{
	for (int i = 0; i < SEGMENT_NUM; i++)
	{
		digit[i].byte = 0;
	}
}

void Container7Seg::Write(int segment, Digit7Seg digit)
{
	this->digit[segment] = digit;
}

void Container7Seg::Init()
{
	GpioInit();
}

void Container7Seg::Cyclic()
{
	static int activeDigit = 0;

	LightUpDigit(activeDigit, digit[activeDigit]);

	activeDigit++;
	activeDigit %= SEGMENT_NUM;
}

void Container7Seg::LightUpDigit(int num, Digit7Seg digit)
{
	// TODO parameter check

	// Segment
	HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, (GPIO_PinState) digit.segment.point);
	HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, (GPIO_PinState) digit.segment.G    );
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, (GPIO_PinState) digit.segment.F    );
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, (GPIO_PinState) digit.segment.E    );
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (GPIO_PinState) digit.segment.D    );
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (GPIO_PinState) digit.segment.C    );
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (GPIO_PinState) digit.segment.B    );
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (GPIO_PinState) digit.segment.A    );

	// Common reset
	static GPIO_TypeDef* ports[3] =
	{
		DCOM0_GPIO_Port,
		DCOM1_GPIO_Port,
		DCOM2_GPIO_Port
	};

	static uint16_t pins[3] =
	{
		DCOM0_Pin,
		DCOM1_Pin,
		DCOM2_Pin
	};

	int prevnum = (num + 2) % 3;

	HAL_GPIO_WritePin(ports[prevnum], pins[prevnum], GPIO_PIN_RESET);

	// Tickle the D flip flops' clock input
	HAL_GPIO_WritePin(DCLK_GPIO_Port, DCLK_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DCLK_GPIO_Port, DCLK_Pin, GPIO_PIN_SET);

	// Common set
	HAL_GPIO_WritePin(ports[num], pins[num], GPIO_PIN_SET);
}

void Container7Seg::GpioInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pins : PAPin PAPin PAPin PAPin */
	GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PCPin PCPin PCPin PCPin */
	GPIO_InitStruct.Pin = DCLK_Pin|D6_Pin|DCOM0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PBPin PBPin PBPin PBPin
	PBPin PBPin PBPin */
	GPIO_InitStruct.Pin = D3_Pin|D1_Pin|D7_Pin|D2_Pin|DEN_Pin|DCOM1_Pin|DCOM2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, D4_Pin|D5_Pin|D0_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, DCLK_Pin|D6_Pin|DCOM0_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, D3_Pin|D1_Pin|D7_Pin|D2_Pin|DEN_Pin|DCOM1_Pin|DCOM2_Pin, GPIO_PIN_RESET);
}
