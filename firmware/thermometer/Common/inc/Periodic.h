#pragma once
#include <cstdint>

class Periodic
{
public:
	virtual void Init() = 0;
	virtual void Cyclic() = 0;

	uint32_t GetPeriod(){return period;}

protected:
	Periodic(uint32_t period_ms);

private:
	uint32_t period;
};
