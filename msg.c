#include "msg.h"
#include <stdlib.h>
#include <string.h>

msg_p msg_list_head = NULL;

msg_p  msg_getNextMessage(uint32_t taskID)
{
	msg_p nextMessage = msg_list_head;

	while (nextMessage != NULL) {
		if (taskID == nextMessage->taskID) 
		{
			break;
		}
		else
		{
			nextMessage = nextMessage->next_msg;
		}
	}

	return nextMessage;
}

void    msg_removeNextMessage(uint32_t taskID)
{
	msg_p nextMessage = msg_list_head;
	msg_p prevMessage = NULL;

	while (nextMessage != NULL) {
		if (taskID == nextMessage->taskID) 
		{
			if (NULL == prevMessage)
			{
				msg_list_head = nextMessage->next_msg;
			}
			else
			{
				prevMessage->next_msg = nextMessage->next_msg;
			}
			free(nextMessage);
			break;
		}
		else
		{
			prevMessage = nextMessage;
			nextMessage = nextMessage->next_msg;
		}
	}

	return;
}

void    msg_addNewMessage(uint32_t taskID, char data[MESSAGE_CAPACITY])
{
	msg_p newMessage = malloc(sizeof(msg_t));
	msg_p nextMessage = msg_list_head;	

	newMessage->taskID = taskID;
	memcpy(&newMessage->data, data, sizeof(newMessage->data));

	if (msg_list_head == NULL) 
	{
		msg_list_head = newMessage;
	} 
	else
	{
		while(1)
		{
			if (nextMessage->next_msg == NULL)
			{
				nextMessage->next_msg = newMessage;
				break;
			}
			else
			{
				nextMessage = nextMessage->next_msg;
			}
		}
	}

	return;
}	
