#include "taskPatch.h"
#include "msg.h"
#include "tasks.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

void replace_char(char NewValue, uintptr_t location);

extern void *main_p;

void taskPatch_execute()
{
	msg_p nextMessage_p = NULL;

	while (NULL != (nextMessage_p = msg_getNextMessage(TASK_PATCH)))
	{
		patchMsg_p patchMessage_p = (patchMsg_p) nextMessage_p;
		
		if (patchMessage_p->patchSize <= 2040)
		{
			for (int char_index = 0; char_index < patchMessage_p->patchSize; char_index++)
			{
				replace_char(patchMessage_p->patch[char_index], patchMessage_p->patchLocation + char_index);
			}
		}
		//printf("Message recieved: id=%d, location=%X, size=%d\n", patchMessage_p->taskID, patchMessage_p->patchLocation, patchMessage_p->patchSize);
		msg_removeNextMessage(TASK_PATCH);
	}
}

void replace_char(char NewValue, uintptr_t location) {
    //  Find page size for this system.
    size_t pagesize = sysconf(_SC_PAGESIZE);

    //  Calculate start and end addresses for the write.
    uintptr_t start =  main_p + location;
    uintptr_t end = start + sizeof NewValue;

    //  Calculate start of page for mprotect.
    uintptr_t pagestart = start & -pagesize;

    //  Change memory protection.
    if (mprotect((void *) pagestart, end - pagestart,
            PROT_READ | PROT_WRITE | PROT_EXEC))
    {
        perror("mprotect");
        exit(EXIT_FAILURE);
    }

    //  Write new bytes to desired location.
    memcpy((void *) start, &NewValue, sizeof NewValue);
	mprotect((void *) pagestart, end - pagestart, PROT_READ | PROT_EXEC);
}
