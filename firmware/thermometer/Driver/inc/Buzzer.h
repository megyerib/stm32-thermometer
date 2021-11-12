#pragma once
#include <output.h>
#include <square_wave.h>
#include "stm32f4xx_hal.h"

class Buzzer : public Output<square_wave_t>
{
public:
	static Buzzer& GetInstance();
	virtual bool Write(const square_wave_t& data) override;

private:
	TIM_HandleTypeDef htim;

	Buzzer();
	void InitTimer();
	void InitGpio();

	static void CalcTimerRegisters(uint32_t cntVal, uint16_t& prescaler, uint16_t& period);
};
