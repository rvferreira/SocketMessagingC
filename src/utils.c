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
int nOnlineUsers = -1;
int nContacts = 0;

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
	nOnlineUsers++;

	if (!nOnlineUsers) 
		onlineUsers = (OnlineUser *)malloc(sizeof(OnlineUser));
	else 
		onlineUsers = (OnlineUser *)realloc(onlineUsers, (nOnlineUsers+1) * sizeof(OnlineUser));
	
	strcpy(onlineUsers[nOnlineUsers].ip, ip);
	
	onlineUsers[nOnlineUsers].port = port;
	onlineUsers[nOnlineUsers].contact = 0;
	
	/* todo usuário começa como válido, se ele cair ele fica 0 */
	onlineUsers[nOnlineUsers].valid = 1;

	printf("\n Add User ip: %s \n",onlineUsers[nOnlineUsers].ip);
}


/*apenas para debugar o código */
void listOnlineUsers(){
	int i;

	for (i=0;i<=nOnlineUsers;i++){
		if(onlineUsers[i].valid) printf("\nUser online Port: %d \n", onlineUsers[i].port);
	}

}