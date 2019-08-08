#include "taskManager.h"
#include "tasks.h"
#include "taskUplink.h"
#include "taskPatch.h"
#include "taskShell.h"

void taskManager_run(uint32_t tick)
{
	switch (tick)
	{
		case TASK_UPLINK:
			taskUplink_execute();	
			break;
		case TASK_PATCH:
			taskPatch_execute();
			break;
		case TASK_SHELL:
			taskShell_execute();
			break;
		case TASK_3:
			break;
		case TASK_4:
			break;
		default:
			break;
	}

	return;
}
