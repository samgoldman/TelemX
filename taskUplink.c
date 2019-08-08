#include "taskUplink.h"
#include "tasks.h"
#include "msg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE (MESSAGE_CAPACITY + 4)

void taskUplink_execute() {
	DIR* FD;
	struct dirent* in_file;
	FILE	*entry_file;
	char buffer[BUFFER_SIZE + 1];
	char filename[1000];

	if (NULL == (FD = opendir("/home/sgoldman/projects/test_sat/uplink")))
	{
        fprintf(stderr, "Error : Failed to open input directory\n");
        return;
    }
	while ((in_file = readdir(FD)))
	{
		/* On linux/Unix we don't want current and parent directories
         * If you're on Windows machine remove this two lines
         */
        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))    
            continue;
		if(in_file->d_type == DT_DIR)
			continue;
        /* Open directory entry file for common operation */
		errno = 0;
		sprintf(filename, "%s/%s", "/home/sgoldman/projects/test_sat/uplink", in_file->d_name);
        entry_file = fopen(filename, "rb");
        if (entry_file == NULL)
        {
            fprintf(stderr, "Error : Failed to open entry file: %s\t%d\n", in_file->d_name, errno);
            return;
        }

        /* Doing some stuff with entry_file : */

        while (fgets(buffer, BUFFER_SIZE + 1, entry_file) != NULL)
        {
        	msg_t newMsg;
			memcpy(&newMsg, buffer, BUFFER_SIZE);

			msg_addNewMessage(newMsg.taskID, newMsg.data);
		}	

		remove(filename);
	}	
}
