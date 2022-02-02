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
	virtual void PeriodicFunction() override;

private:
	GPIO_TypeDef* gpio_port;

	uint16_t filteredValue = 0x00000000; // Bitfield
	uint16_t risingEdges   = 0x00000000; // Bitfield

	uint16_t meas[DEBOUNCING_WINDOW_SIZE] = {0};
	uint16_t i_meas = 0; // Measurement index

	Debouncer();
};
