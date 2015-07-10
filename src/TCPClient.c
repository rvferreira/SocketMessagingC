/*
 ============================================================================
 Name        : TCPClient.c
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */

#include "TCPClient.h"
#include "message.h"

int sockClient;

/* estabelece uma conexão com um servidor online */
int establishedConnection(char ip[]) {
    struct hostent *host;
    struct sockaddr_in server_addr;
    ServerMessage recv_data;

    host = gethostbyname(ip);

    if (!strcmp(ip, "0")) {
        return 1;
    }
    /* cria uma variável do tipo sock */
    if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error: failed function socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEFAULT_PORT);
    server_addr.sin_addr = *((struct in_addr *) host->h_addr);
    bzero(&(server_addr.sin_zero), 8);

    if (connect(sockClient, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1) {
        perror("Server offline");
        return 1;
    }

    recv(sockClient, (void *) &recv_data, sizeof(recv_data), 0);

    // mensagem emitida do servidor
    printf("\n %s \n", recv_data.message);
    getchar();

    return 0;

}

void closeConnectionServer() {
    ServerMessage m;
    strcpy(m.message, "close");
    strcpy(m.origin, myIP);
    /* avisa o servidor que fechou a conexão */
    send(sockClient, (void *) &m, sizeof(m), 0);
    close(sockClient);
}

void sendMessage(ServerMessage m) {
    ServerMessage reply;

    /* envia mensagem para o servidor */
    if (send(sockClient, (void *) &m, sizeof(m), 0) == -1) {
        printf("Error: Message \n");
    }

    /*servidor confirma o recebimento da mensagem */
    recv(sockClient, (void *) &reply, sizeof(reply), 0);
    printf("\n %s \n", reply.message);
}

void receiveMessage() {
    ServerMessage reply;

    /* fica esperando uma mensagem do servidor */
    recv(sockClient, (void *) &reply, sizeof(reply), 0);

    /* servidor enviando a lista de contatos */
    if (!strcmp(reply.message, "broadcast_list_online")) {
        send(sockClient, (void *) &reply, sizeof(reply), 0);

        sleep(1);
        recv(sockClient, &nOnlineUsers, sizeof(int), 0);
        send(sockClient, "OK", sizeof("OK"), 0);
        sleep(1);

        onlineUsers = realloc(NULL, sizeof(OnlineUser) * (nOnlineUsers + 1));

        recv(sockClient, onlineUsers, sizeof(onlineUsers), 0);
        send(sockClient, "OK", sizeof("OK"), 0);

    }

    return;
}