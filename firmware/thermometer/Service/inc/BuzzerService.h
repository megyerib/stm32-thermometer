#pragma once
#include "Output.h"
#include "Periodic.h"
#include "squarewave.h"

class BuzzerService : public Periodic
{
public:
	static void Start();

	virtual void Init() override;
	virtual void Cyclic() override;

private:
	Output<SquareWave>* Buzzer;
	bool state;

	BuzzerService();

	void PortInit();
};
