/*
 ============================================================================
 Name        : message.h
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */


#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "utils.h"

#define MESSAGE_SIZE 144
#define MESSAGE_BOX_SIZE 10

/* tipo de mensagem que um cliente pode mandar para o servidor */
typedef enum mt {
	/* ele manda para outro cliente uma mensagem */
	simpleTextSingleTarget = 1,
	/* manda para todos os clientes de um grupo uma mensagem */
	simpleTextBroadTarget = 2,
	/* quer saber quem está online */
	onlineUserListSize = 3,
	/* identificação do cliente */
	clientIdentification = 4,
	/* resposta do servidor */
	responseServer = 5,
} MessageType;

typedef struct m {
	MessageType messageType;
	char origin[15];
	char target[15];
	char message[MESSAGE_SIZE];
} ServerMessage;

extern ServerMessage MessageBox[];
extern ServerMessage *newMessage;
extern sem_t newMessage_sem;

ServerMessage* setMessage(MessageType, char[], char[]);
void copyMessage(ServerMessage *destiny, ServerMessage *origin);

int sendMessageContactMethod();
void sendMessageGroupMethod();

#include "TCPClient.h"

#endif /* MESSAGE_H_ */
