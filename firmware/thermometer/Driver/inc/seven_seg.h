#pragma once

#include "output.h"
#include "digit.h"
#include "Periodic.h"

#define DIGIT_NUM 3

class SevenSeg : public Output<digit_t[DIGIT_NUM]>,
                 public Periodic
{
public:
	static SevenSeg& GetInstance();
	virtual bool Write(const digit_t (&input)[DIGIT_NUM]) override;

	virtual void PeriodicFunction() override;

private:
	SevenSeg();

	digit_t digit[3] = {DIGIT_NONE, DIGIT_NONE, DIGIT_NONE};
	void LightUpDigit(int segment, digit_t digit);
};
