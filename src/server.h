/*
 ============================================================================
 Name        : server.h
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */


#ifndef SERVER_H_
#define SERVER_H_

#include <pthread.h> 
#include "utils.h"
#include "client.h"

extern  char ipClient[15];
extern  char ipServer[15];
extern int portClient;

void *runServer(void *);
void *connection_handler(void *); 
void *broadcast_list_online(void *);  //broadcast para todos os usuários
#endif /* SERVER_H_ */
