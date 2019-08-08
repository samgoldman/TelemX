#ifndef _TASK_PATCH_H
#define _TASK_PATCH_H

#include <stdint.h>

typedef struct patchMsg
{
	uint32_t 	taskID;
	uint32_t	patchLocation;
	uint32_t 	patchSize;
	char		patch[2040];
	struct msg * next_msg;
} patchMsg_t, *patchMsg_p;

void taskPatch_execute();

#endif
