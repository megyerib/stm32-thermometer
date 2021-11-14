#pragma once

#include "Periodic.h"
#include "Input.h"

class Temperature : public Input<float>,
                    public Periodic
{
public:
	static Temperature& GetInstance();

	virtual bool Read(float& temp) override;
	virtual void Cyclic() override;

private:
	bool valid = false;
	bool has_valid_sample = false;
	float temp = 0;

	Temperature();
};
