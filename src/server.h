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

void runServer();
void *connection_handler(void *); 
#endif /* SERVER_H_ */
