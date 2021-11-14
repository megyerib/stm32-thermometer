#pragma once

#include <cstdint>
#include "Periodic.h"
#include "stm32f446xx.h"

const int DEBOUNCING_WINDOW_SIZE = 8;

class Debouncer : public Periodic
{
public:
	static Debouncer& GetInstance();

	bool GetValue(uint16_t mask);
	bool GetRisingEdge(uint16_t mask);
	void ClearRisingEdges();
	virtual void Cyclic() override;

private:
	GPIO_TypeDef* gpio_port;

	uint32_t filteredValue = 0x00000000; // Bitfield
	uint32_t risingEdges   = 0x00000000; // Bitfield

	uint32_t meas[DEBOUNCING_WINDOW_SIZE] = {0};
	uint32_t iMeas = 0;

	Debouncer();
};
