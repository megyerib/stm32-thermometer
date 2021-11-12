#include "Buzzer.h"

Buzzer* Buzzer::GetInstance()
{
	static Buzzer instance;
	return &instance;
}

// TODO handle invalid inputs

int32_t Buzzer::Write(const SquareWave& data)
{
	// 1 SET FREQUENCY

	// Prescaler * period = 180M / freq;
	// Prescaler: 16 bit
	// Period:    16 bit

	uint16_t prescaler, period, threshold;
	uint32_t product = (uint32_t)(1.8e8 / data.frequency);

	CalcTimerRegisters(product, prescaler, period);

	threshold = ((period + 1) * data.dutyCycle) - 1; // TODO overrun!

	// Write registers
	TIM1->PSC  = prescaler;
	TIM1->ARR  = period;
	TIM1->CCR4 = threshold;

	return OUTPUT_WRITE_OK;
}

void Buzzer::CalcTimerRegisters(uint32_t cntVal, uint16_t& prescaler, uint16_t& period)
{
	uint16_t* upper = (uint16_t*)&cntVal;
	prescaler = 1;

	while (upper[1] != 0)
	{
		cntVal >>= 1;
		prescaler <<= 1;
	}

	prescaler--;

	period = upper[0];
	period--;
}

Buzzer::Buzzer()
{
	InitTimer();
	InitGpio();

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	TIM1->CCR4 = 0;
}

void Buzzer::InitTimer()
{
	__HAL_RCC_TIM1_CLK_ENABLE();

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 180-1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 10000-1;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
		//Error_Handler();
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
	{
		//Error_Handler();
	}

	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
	{
		//Error_Handler();
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		//Error_Handler();
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	{
		//Error_Handler();
	}

	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
	{
		//Error_Handler();
	}
}

void Buzzer::InitGpio()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();

	/**TIM1 GPIO Configuration
	PA11     ------> TIM1_CH4
	*/
	GPIO_InitStruct.Pin       = GPIO_PIN_11;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
