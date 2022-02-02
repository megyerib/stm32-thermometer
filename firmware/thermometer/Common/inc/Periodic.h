#pragma once

#include <cstdint>

class Periodic
{
public:
	const uint32_t period_ms;

	Periodic(uint32_t period_ms) : period_ms(period_ms) {};
    virtual void PeriodicFunction() = 0;
};
