/*
 * message.c
 *
 *  Created on: Jun 9, 2015
 *      Author: rferreira
 */

#include "message.h"
#include "TCPClient.h"

ServerMessage MessageBox[MESSAGE_BOX_SIZE];

void insertMessageIntoMessageBox(ServerMessage *new){
	MessageBox[4] = MessageBox[3];
	MessageBox[3] = MessageBox[2];
	MessageBox[2] = MessageBox[1];
	MessageBox[1] = MessageBox[0];
	MessageBox[0] = *new;
}

int serverRequest(ServerMessage m){
	sendMessage(m);
	getchar();

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
	else {
		return EXIT_FAILURE;
	}

	char message[MESSAGE_SIZE];
	printf("Message: ");
	scanf("%s", message);

	ServerMessage *new = malloc(sizeof(ServerMessage));
	new->messageType = simpleTextSingleTarget;
	strcpy(new->target, onlineUsers[i].ip);
	strcpy(new->message, message);

	serverRequest(*new);

	return EXIT_SUCCESS;

}

void sendMessageGroupMethod(){
	char message[MESSAGE_SIZE];
	printf("Message: ");
	fgets(message, sizeof(message),stdin);

	ServerMessage *new = malloc(sizeof(ServerMessage));
	new->messageType = simpleTextBroadTarget;
	strcpy(new->target, "all");
	strcpy(new->message, message);

	serverRequest(*new);
}

void updateMessagebox(){

}
