#pragma once

#include <dma_uart_f4.h>

class NucleoUart : public DmaUartF4
{
public:
	static NucleoUart& GetInstance();

private:
	NucleoUart();
};
