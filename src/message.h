/*
 * message.h
 *
 *  Created on: Jun 9, 2015
 *      Author: rferreira
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "utils.h"

#define MESSAGE_SIZE 144

typedef enum mt {
	simpleTextSingleTarget = 1,
	simpleTextBroadTarget = 2,
	onlineUserListSize = 3,
	clientIdentification = 4,
} MessageType;

typedef struct m {
	MessageType messageType;
	char target[15];
	char message[MESSAGE_SIZE];
} serverMessage;

int sendMessageContactMethod();
void sendMessageGroupMethod();

void updateMessageBox();

#endif /* MESSAGE_H_ */
