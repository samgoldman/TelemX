#include "taskShell.h"
#include "msg.h"
#include "tasks.h"

#include <stdio.h>
#include <dlfcn.h>

void taskShell_execute()
{
    msg_p nextMessage_p = NULL;

    while (NULL != (nextMessage_p = msg_getNextMessage(TASK_SHELL)))
    {
        shellMsg_p shellMessage_p = (shellMsg_p) nextMessage_p;
        //printf("Message recieved: id=%d, function name: %s\n", shellMessage_p->taskID, shellMessage_p->functionName);
       	void *hdl; // symbol table handle
		int (*fnc_ptr)();

		hdl = dlopen(NULL, 0);
		fnc_ptr = dlsym(hdl, shellMessage_p->functionName);
		if (NULL != fnc_ptr) 
		{
			printf("Shell result: %X\n", fnc_ptr()); 
		}
		msg_removeNextMessage(TASK_SHELL);
    }
}
