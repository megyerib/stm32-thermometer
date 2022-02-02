#pragma once

#include "Periodic.h"
#include <cstdlib>

class FreeRtosTask
{
public:
	Periodic& periodic;

	FreeRtosTask(Periodic& p, size_t stack_size, unsigned int prio, const char* name);
};
