#pragma once
#include "Periodic.h"
#include "Digit7Seg.h"

#define SEGMENT_NUM 3

class Container7Seg : public Periodic
{
public:
	static Container7Seg* GetInstance();
	void Write(int segment, Digit7Seg digit);

	virtual void Init() override;
	virtual void Cyclic() override;

private:
	Digit7Seg digit[3];

	Container7Seg();
	void LightUpDigit(int segment, Digit7Seg digit);
	void GpioInit();
};
