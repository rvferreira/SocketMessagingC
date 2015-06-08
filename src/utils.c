/*
 * utils.c
 *
 *  Created on: Jun 6, 2015
 *      Author: rferreira
 */

#include "utils.h"

int debugMode = 0;
int serverMode = 0;

onlineUser *onlineUsers;
int nOnlineUsers = 3;
int nContacts = 1;

void variablesInit(){
	onlineUsers = malloc(nOnlineUsers * sizeof(onlineUser));
	strcpy(onlineUsers[0].ip, "120.0.0.1");
	onlineUsers[0].contact = 1;

	strcpy(onlineUsers[1].ip, "120.0.0.2");
	onlineUsers[1].contact = 0;

	strcpy(onlineUsers[2].ip, "120.0.0.3");
	onlineUsers[2].contact = 0;
}
