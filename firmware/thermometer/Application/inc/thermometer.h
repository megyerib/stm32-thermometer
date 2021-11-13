#pragma once

#include "Periodic.h"

class Thermometer : public Periodic
{
public:
	static void Start();

private:
	Thermometer();
	virtual void Cyclic() override;
};
