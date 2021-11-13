#pragma once

#include "Input.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"

class TC77 : Input<float>
{
public:
	static TC77& GetInstance();
	virtual bool Read(float& temp) override;

private:
	SPI_HandleTypeDef hspi;

	TC77();

	void GpioInit();
	void SpiInit();
};
