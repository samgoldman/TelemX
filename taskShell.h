#ifndef _TASK_SHELL_H
#define _TASK_SHELL_H

#include <stdint.h>

typedef struct shellMsg
{
	uint32_t taskID;
	char     functionName[2048];
} shellMsg_t, *shellMsg_p;

void taskShell_execute();

#endif
