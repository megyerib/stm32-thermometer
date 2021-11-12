#pragma once
#include "Output.h"
#include "Digit7Seg.h"

class DisplayService : public Output<float>
{
public:
	static DisplayService* GetInstance();
	int32_t Write(const float& data) override;

private:
	Output<Digit7Seg>* digit[3];

	DisplayService();
	void PortInit();
};
