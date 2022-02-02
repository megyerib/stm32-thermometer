#pragma once
#include <digit.h>
#include <output.h>
#include "Periodic.h"

class Blinker : public Periodic, public Output<bool>
{
public:
	Blinker(Output<bool>& led);
	virtual bool Write(const bool& on) override;

private:
	Output<bool>& led;
	bool state = false;
	bool enabled = false;

	virtual void PeriodicFunction() override;
};
