#pragma once
#include "Output.h"
#include "squarewave.h"
#include "stm32f4xx_hal.h"

class Buzzer : public Output<SquareWave>
{
public:
	static Buzzer* GetInstance();
	virtual int32_t Write(const SquareWave& data) override;

private:
	TIM_HandleTypeDef htim1;

	Buzzer();
	void InitTimer();
	void InitGpio();

	static void CalcTimerRegisters(uint32_t cntVal, uint16_t& prescaler, uint16_t& period);
};
