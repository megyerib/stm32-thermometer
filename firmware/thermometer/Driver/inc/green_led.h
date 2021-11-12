#pragma once
#include <output.h>

class GreenLed : public Output<bool>
{
public:
	virtual bool Write(const bool& data) override;
	static GreenLed& GetInstance();

private:
	GreenLed();
};
