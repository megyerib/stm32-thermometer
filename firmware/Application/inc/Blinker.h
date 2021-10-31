#pragma once
#include "Output.h"
#include "Periodic.h"
#include "Digit7Seg.h"

class Blinker : public Periodic
{
public:
	static void Start();

	virtual void Init() override;
	virtual void Cyclic() override;

private:
	Output<bool>* Led;
	Output<float>* display;
	bool state;
	int32_t num;

	Blinker();

	void PortInit();
};
