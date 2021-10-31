#include "Display7Seg.h"
#include "Container7Seg.h"

Display7Seg* Display7Seg::GetInstance(uint32_t num)
{
	static Display7Seg digits[3] = {0, 1, 2};

	return &digits[num];
}

int32_t Display7Seg::Write(const Digit7Seg& data)
{
	static Container7Seg* fullDisplay = Container7Seg::GetInstance();

	fullDisplay->Write(num, data);

	return OUTPUT_WRITE_OK;
}

Display7Seg::Display7Seg(uint32_t num)
{
	this->num = num;
}
