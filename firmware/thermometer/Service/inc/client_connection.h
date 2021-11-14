#pragma once

#include "Output.h"
#include "app_state.h"
#include "transmitter.h"

class ClientConnection : public Output<app_state_t>
{
public:
	ClientConnection(Transmitter& transmitter);
	virtual bool Write(const app_state_t& state) override;

private:
	Transmitter& transmitter;
};
