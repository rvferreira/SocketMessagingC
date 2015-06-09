/*
 ============================================================================
 Name        : utils.h
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */

#ifndef UTILS_H_
#define UTILS_H_

#define IP_SIZE 15

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define DEFAULT_PORT 7013

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

extern int debugMode;
extern int serverMode;		// Global variable that defines whether this is a Client or a Server

extern int nOnlineUsers;
extern int nContacts;

enum menu {
	addContact = 1,
	listContacts = 2,
	deleteContact = 3,
	sendMessageContact = 4,
	sendMessageGroup = 5,
	closeConnection = 6,
};

typedef struct ou {
	char ip[15];
	int contact;
//	struct onlineUser *next;
} OnlineUser;

extern OnlineUser *onlineUsers;

void variablesInit();

#endif
