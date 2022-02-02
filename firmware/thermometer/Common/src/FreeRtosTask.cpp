#include "Periodic.h"
#include "FreeRtosTask.h"
#include "FreeRTOS.h"
#include "task.h"

void CyclicTask(void* p);

FreeRtosTask::FreeRtosTask(
	Periodic& periodic,
	size_t stack = configMINIMAL_STACK_SIZE,
	unsigned int prio = 1,
	const char* name = ""
) : periodic(periodic)
{
	xTaskCreate(CyclicTask, name, stack, this, prio, nullptr);
}

void CyclicTask(void* p)
{
	FreeRtosTask* task = (FreeRtosTask*) p;
	Periodic& periodic = task->periodic;

	while (1) {
		periodic.PeriodicFunction();
		vTaskDelay(periodic.period_ms);
	}
}
