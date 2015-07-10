/*
 ============================================================================
 Name        : utils.c
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */


#include "utils.h"

int debugMode = 0;
int serverMode = 0;
char myIP[15];
int myPort;

OnlineUser *onlineUsers;
int nOnlineUsers = 0;

/*
void variablesInit(){
	onlineUsers = malloc(nOnlineUsers * sizeof(OnlineUser));
	strcpy(onlineUsers[0].ip, "120.0.0.1");
	onlineUsers[0].contact = 1;

	strcpy(onlineUsers[1].ip, "120.0.0.2");
	onlineUsers[1].contact = 0;

	strcpy(onlineUsers[2].ip, "120.0.0.3");
	onlineUsers[2].contact = 0;
}
*/

void addOnlineUser(char *ip, int port){
	if (!nOnlineUsers) {
		onlineUsers = (OnlineUser *) malloc(sizeof(OnlineUser) * BACKLOG);
	}
	
	strcpy(onlineUsers[nOnlineUsers].ip, ip);
	onlineUsers[nOnlineUsers].port = port;
	onlineUsers[nOnlineUsers].contact = 1;
	onlineUsers[nOnlineUsers].valid = 1;
	onlineUsers[nOnlineUsers].sock = sockClient;

	nOnlineUsers++;
}


/*apenas para debugar o código */
void listOnlineUsers(){
	int i;

	for (i=0;i<nOnlineUsers;i++){
		if(onlineUsers[i].valid) printf("User %s online at port: %d \n", onlineUsers[i].ip, onlineUsers[i].port);
	}

}