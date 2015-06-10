/*
 * client.c
 *
 *  Created on: Jun 6, 2015
 *      Author: rferreira
 */

#include "client.h"

#define CTRLD 	4

MENU *mainMenu;
ITEM **mainMenuItems;
int menuItemSelected = -1;

char *choices[] = {
	"Add Contact",
	"List Contacts",
	"Delete Contact",
	"New Message",
	"New Group Message",
	"Exit",
};

int listContactsMethod(){
	int i;
	printf("Contact List: \n");
	printf("\tID\tIP ADDRESS\n");
	for (i=0; i<nOnlineUsers; i++){
		if (onlineUsers[i].contact){
			printf("\t%d\t%s\n", i, onlineUsers[i].ip);
		}
	}
	return EXIT_SUCCESS;
}

int deleteContactMethod(){
	int i;
	listContactsMethod();
	printf("\nEnter the contact ID to be deleted or -1 for cancel: ");
	scanf("%d", &i);

	if (onlineUsers[i].contact){
		onlineUsers[i].contact = 0;
		printf("Contact successfully deleted.\n");
	}
	else if (i == -1){
		return EXIT_SUCCESS;
	}
	else{
		printf("Not a contact.\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int addContactMethod(){
	char ip[IP_SIZE];
	printf("Type the IP address of the contact: ");
	scanf("%s", ip);

	OnlineUser *try = NULL;

	int i;
	for (i = 0; i < nOnlineUsers; i++){
		if (!strcmp(ip, onlineUsers[i].ip)){
			try = &onlineUsers[i];
		}
	}

	if (try == NULL){
		printf("Invalid user's IP address.\n");
		return EXIT_FAILURE;
	}
	else if (try->contact){
		printf("Contact's already on the list of contacts.\n");
		return EXIT_FAILURE;
	}
	else{
		try->contact = 1;
		nContacts++;
		printf("Contact successfully added to contact list.\n");
	}


	return EXIT_SUCCESS;
}

void changeState(){
	switch (menuItemSelected){
	case addContact:
		addContactMethod();
		break;
	case listContacts:
		listContactsMethod();
		break;
	case deleteContact:
		deleteContactMethod();
		break;
	case sendMessageContact:
		listContactsMethod();
		sendMessageContactMethod();
		break;
	case sendMessageGroup:
		sendMessageGroupMethod();
		break;
	case closeConnection:
		printf("Closing Connection...\n");
		closeConnectionServer();
		break;
	}
}

void startApp(){
	int c, nChoices;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	nChoices = ARRAY_SIZE(choices);
	mainMenuItems = (ITEM **)calloc(nChoices + 1, sizeof(ITEM *));

	char num[ARRAY_SIZE(choices)][2];

	int i;
	for(i = 0; i < nChoices; ++i) {
		sprintf(num[i], "%d", i+1);
		mainMenuItems[i] = new_item(num[i], choices[i]);
	}
	mainMenuItems[nChoices] = (ITEM *)NULL;

	mainMenu = new_menu((ITEM **)mainMenuItems);
	mvprintw(LINES - 2, 0, "F3 to Exit");
	post_menu(mainMenu);
	refresh();

	while((c = getch()) != KEY_F(3))
	{
		int endLoop = 0;
		switch(c)
		{	case KEY_DOWN:
				menu_driver(mainMenu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(mainMenu, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
				menuItemSelected = atoi(item_name(current_item(mainMenu)));
				endLoop = 1;
				break;
		}
		if (endLoop) break;
	}

	if (menuItemSelected == -1) menuItemSelected = closeConnection;

	free_item(mainMenuItems[0]);
	free_item(mainMenuItems[1]);
	free_menu(mainMenu);
	endwin();
}

int tryConnect(char ip[]){
	
	return (establishedConnection(ip));

}

void runClient(char ip[]) {
	variablesInit();
	if (!tryConnect(ip)){
		while (menuItemSelected != closeConnection){
			system("clear");
			menuItemSelected = -1;
			startApp();
			changeState();
			if ((menuItemSelected!=sendMessageContact)
					&&((menuItemSelected!=sendMessageGroup)))
				getch();
		}
	}
}
