#pragma once
#include "Digit7Seg.h"
#include "Output.h"

class Display7Seg : public Output<Digit7Seg>
{
public:
	static Display7Seg* GetInstance(uint32_t num);
	virtual int32_t Write(const Digit7Seg& data) override;

private:
	uint32_t num;
	Display7Seg(uint32_t num);
};
