/*
 ============================================================================
 Name        : message.c
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */


#include "message.h"
#include "TCPClient.h"

ServerMessage MessageBox[MESSAGE_BOX_SIZE];
ServerMessage *newMessage = NULL;
sem_t newMessage_sem;

ServerMessage *setMessage(MessageType t, char target[], char message[]) {
    ServerMessage *new = malloc(sizeof(ServerMessage));

    new->messageType = simpleTextSingleTarget;
    strcpy(new->origin, myIP);
    strcpy(new->target, target);
    strcpy(new->message, message);
    new->port = myPort;

    return new;
}

void copyMessage(ServerMessage *destiny, ServerMessage *origin) {
    destiny->messageType = origin->messageType;
    strcpy(destiny->origin, origin->origin);
    strcpy(destiny->target, origin->target);
    strcpy(destiny->message, origin->message);
}

int sendMessageContactMethod() {
    int i;
    printf("\nEnter the ID of the message target or -1 for cancel: ");
    scanf("%d", &i);
    if (i == -1) {
        return EXIT_SUCCESS;
    }
    else if (!onlineUsers[i].contact) {
        printf("Not a contact.\n");
        getch();
        return EXIT_FAILURE;
    }

    char message[MESSAGE_SIZE];
    getchar();
    printf("Message: ");
    fgets(message, sizeof(message), stdin);
    scanf("%s",message);
    if (send(onlineUsers[i].sock, message, MESSAGE_SIZE, 0) == -1) {
        printf("Error: Message \n");
    }

    return EXIT_SUCCESS;
}

void sendMessageGroupMethod() {
    int i;
    char message[MESSAGE_SIZE];
    printf("Message: ");
    fgets(message, sizeof(message), stdin);

    for (i=0; i<nOnlineUsers ; i++){
        if (onlineUsers[i].contact){
            if (send(onlineUsers[i].sock, message, MESSAGE_SIZE, 0) == -1) {
                printf("Error: Message \n");
            }
        }
    }   

    return EXIT_SUCCESS;
}
