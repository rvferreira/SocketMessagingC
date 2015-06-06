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

#define DEFAULT_PORT 7013

int debugMode = 0;
int serverMode = 0;		// Global variable that defines whether this is a Client or a Server

enum menu {
	addContact = 1,
	listContacts = 2,
	deleteContact = 3,
	sendMessageContact = 4,
	sendMessageGroup = 5,
	closeConnection = 6,
};

#endif
