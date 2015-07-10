/*
 ============================================================================
 Name        : server.c
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */

/* contém a assinatura das funções e os includes necessários */
#include "server.h"
#include "message.h" 
/*
  O código do socket foi baseado no disponibilizado pelo site da
  disciplina "moodle.lasdpc.icmc.usp.br"
*/

char ipClient[15], ipServer[15];
int portClient;

void *runServer(void *thread_id){

    //Variáveis
    int sock, *new_sock, connected, iTrue = 1;
    struct sockaddr_in server_addr, client_addr;
    int sin_size;

    /* AF_INET = "SOCK_STREAM": Conexão TCP
    Verifica se houve algum problema com o socket */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error: failed function socket ");
        exit(1);
    }


    /* por enquanto SO_REUSEADDR = FALSE, aceita uma conexão por endereço */
    if (setsockopt(sock, SOL_SOCKET,SO_REUSEADDR, &iTrue,sizeof(int)) == -1)
    {
        perror("Error: failed function setsockopt");
        exit(1);
    }

    //configura o endereço de destino
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEFAULT_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero),8);

    /* informa endereço ao socket */
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {

        perror("Error: failed function bind");
        exit(1);
    }


    if (listen(sock, BACKLOG) == -1)
    {
        perror("Error: failed function listen");
        exit(1);
    }

    strcpy(ipServer,inet_ntoa(server_addr.sin_addr));

    /* servidor fica ouvindo as requisições dos clientes */
    if (debugMode) printf("\nServer TCP waiting for connections in port 7000... \n");
    fflush(stdout);

    // Variavel para armazenar o tamanho de endereco do cliente conectado
    sin_size = sizeof(struct sockaddr_in);

    while(connected = accept(sock,(struct sockaddr*)&client_addr,(socklen_t*)&sin_size))
    {

        // addOnlineUser(inet_ntoa(client_addr.sin_addr));
        if (debugMode) printf("\nConnection accepted of (%s , %d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        strcpy(ipClient,inet_ntoa(client_addr.sin_addr));
        portClient = ntohs(client_addr.sin_port);
        // criação de threads para a troca de mensagem com o servidor
        pthread_t thread_id;

        new_sock = malloc (1);
        *new_sock = connected;

        if(pthread_create( &thread_id , NULL , connection_handler , (void*) new_sock) < 0)
        {
            perror("could not create thread");
            exit(1);
        }

        if (connected < 0)
        {
            perror("accept failed");
            exit(1);
        }

    }

    close(sock);
    return NULL;
}

/* uma conexão aberta para cada cliente, através do uso de threads */
void *connection_handler(void *sock){
    // captura o descritor de socket 
    int connected = *(int*) sock;
    ServerMessage recv_data, response_server;
    int bytes_recv;


    /* o server sempre é o primeiro [0] a responder */
    strcpy(response_server.origin,ipServer);

    /* como o usuário acabou de ser adicionado pegamos seu ip */
    strcpy(response_server.target,ipClient);

    /* pegando sua porta */
    response_server.port = portClient;

    response_server.messageType = responseServer;
    strcpy(response_server.message,"Your Successful Connection!");

    // Loop para manter a troca de mensagens
    while (1){

        // Função send(int socket, void*buffer, size_t size, int flags)
        send(connected, (void *)&response_server, sizeof(response_server), 0);

        sleep(1);

        // Funcao recv (int socket, void *buffer, size_t size, int flags)        
        bytes_recv = recv(connected, (void *)&recv_data, sizeof(recv_data), 0);

        if (strcmp(recv_data.message,"close") == 0 && bytes_recv)
        {
            close(connected);

            int j;

            for (j=0; j<=nOnlineUsers; j++){
                if (!strcmp(recv_data.origin, onlineUsers[j].ip)){
                    onlineUsers[j].valid = 0;
                }
            }

            listOnlineUsers();

            if (debugMode) printf("\nLost connection... \n");
            fflush(stdout);
            break;
        }
        else {
            if (debugMode) printf("\n Message received: %s \n" , recv_data.message);
            strcpy(response_server.message,"Your message was sent successfully!");
        }

        fflush(stdout);
    }
    free(sock);
    pthread_exit(0);
}