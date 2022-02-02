#pragma once

#include "Periodic.h"
#include "Input.h"

class Temperature : public Input<float>,
                    public Periodic
{
public:
	Temperature(Input<float>& sensor);

	virtual bool Read(float& temp) override;
	virtual void PeriodicFunction() override;

private:
	Input<float>& sensor;
	bool valid = false;
	bool has_valid_sample = false;
	float temperature = 0;
};
