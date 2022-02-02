#pragma once
#include <output.h>
#include "Periodic.h"

class AlarmSound : public Periodic,
                   public Output<bool>
{
public:
	static AlarmSound& GetInstance();
	virtual void PeriodicFunction() override;
	virtual bool Write(const bool& on) override;

private:
	bool enable = false;
	bool state = false;

	AlarmSound();
};
