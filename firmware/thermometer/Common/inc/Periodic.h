#pragma once
#include <cstdint>

class Periodic
{
public:
	uint32_t GetPeriod(){return period;}

    virtual void Cyclic() = 0;

protected:
	Periodic(uint32_t period_ms);

private:
	uint32_t period;
};
