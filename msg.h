#ifndef _MSG_H
#define _MSG_H

#include <stdint.h>

#define MESSAGE_CAPACITY 2048

typedef struct msg
{
	uint32_t	taskID;
	char		data[MESSAGE_CAPACITY];
	struct msg * next_msg;
} msg_t, *msg_p;

msg_p	msg_getNextMessage(uint32_t taskID);
void	msg_removeNextMessage(uint32_t taskID);
void	msg_addNewMessage(uint32_t taskID, char newMsg[MESSAGE_CAPACITY]);

#endif
