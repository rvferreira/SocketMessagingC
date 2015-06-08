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

char *choices[] = {
	"Add Contact",
	"listContacts",
	"deleteContact",
	"sendMessageContact",
	"sendMessageGroup",
	"Exit",
};

void changeState(int menuItemSelected){
	switch (menuItemSelected){
		case 5: {
			printf("Closing Connection...\n");
			break;
		}
	}
}

void startApp(){
	int c, nChoices;
	int menuItemSelected = -1;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	nChoices = ARRAY_SIZE(choices);
	mainMenuItems = (ITEM **)calloc(nChoices + 1, sizeof(ITEM *));

	char num[ARRAY_SIZE(choices)][2];

	int i;
	for(i = 0; i < nChoices; ++i) {
		sprintf(num[i], "%d", i);
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

	if (menuItemSelected == -1) menuItemSelected = 5;

	free_item(mainMenuItems[0]);
	free_item(mainMenuItems[1]);
	free_menu(mainMenu);
	endwin();

	changeState(menuItemSelected);
}

int tryConnect(){
	return EXIT_SUCCESS;
}

void runClient() {
	if (!tryConnect()){
		startApp();
	}
}
