#pragma once
#include "Output.h"

class GreenLed : public Output<bool>
{
public:
	virtual int32_t Write(const bool& data) override;
	static GreenLed* GetInstance();

private:
	GreenLed();
	void Init();
};
