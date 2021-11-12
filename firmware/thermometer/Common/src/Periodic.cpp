#include "Periodic.h"
#include "FreeRTOS.h"
#include "task.h"

void CyclicTask(void* p);

Periodic::Periodic(uint32_t period_ms)
{
	period = period_ms;

	xTaskCreate(CyclicTask, "asd", 128, this, 1, nullptr);
}

void CyclicTask(void* p)
{
	Periodic* task = (Periodic*) p;

	while (1)
	{
		task->Cyclic();
		vTaskDelay(task->GetPeriod());
	}
}
