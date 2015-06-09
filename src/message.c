/*
 * message.c
 *
 *  Created on: Jun 9, 2015
 *      Author: rferreira
 */

#include "message.h"

int serverRequest(MessageType type, char target, char *message){
	return 0;
}

int sendMessageContactMethod(){
	int i;
	printf("\nEnter the ID of the message target or -1 for cancel: ");
	scanf("%d", &i);

	if (!onlineUsers[i].contact){
		printf("Not a contact.\n");
		getch();
		return EXIT_FAILURE;
	}
	else if (i == -1){
		return EXIT_SUCCESS;
	}

	char message[MESSAGE_SIZE];
	printf("\nMessage: ");
	scanf("%s", message);

	serverRequest(simpleTextSingleTarget, onlineUsers[i].contact, message);

	return EXIT_SUCCESS;

}

void sendMessageGroupMethod(){
	char message[MESSAGE_SIZE];
	printf("Message: ");
	scanf("%s", message);

	serverRequest(simpleTextBroadTarget, "all", message);
}

void updateMessagebox(){

}
