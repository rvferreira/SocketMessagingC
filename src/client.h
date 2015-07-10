/*
 ============================================================================
 Name        : client.h
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "message.h"
#include "TCPClient.h"
#include <menu.h>

extern int sender;

void runClient();
void threadReceiveMessage(char *);
#endif /* CLIENT_H_ */
