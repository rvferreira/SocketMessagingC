/*
 ============================================================================
 Name        : TCPClient.h
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include "utils.h"
#include "message.h"

int establishedConnection(char *);
void closeConnectionServer();
void sendMessage(ServerMessage);

#endif /* TCPCLIENT_H_ */