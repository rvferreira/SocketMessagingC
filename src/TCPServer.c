/*
 ============================================================================
 Name        : TPCServer.c
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */

#include <sys/types.h>   // Definicao de tipos
#include <sys/socket.h>  // Biblioteca de estrutara de sockets
#include <netinet/in.h>  // Define os padroes de protocolo IP
#include <arpa/inet.h>   // Converte enderecos hosts
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Define constantes POSIX
#include <errno.h>  // Utilizado para capturar mensagens de erro
#include <pthread.h> 

void *connection_handler(void *); 

int main(int argc, char *argv[])
{
   
  //Variaveis necessárias para criar a conexão como servidor
   int sock, connected, bytes_recv, i, true = 1;
   struct sockaddr_in server_addr, client_addr;
   int sin_size;

   // criar o socket 
   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
   {
     perror("Error create socket");
     exit(1);
   }
   else {
      if (debugMode){
         printf("Create an unbound socket...\n"); 
      }
   }
 
   // seta opções do socket 
   if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &true,sizeof(int)) == -1)
   {
      perror("Erro Setsockopt");
      exit(1);
   }


   // Configura o endereco de destino
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(DEFAULT_PORT);
   server_addr.sin_addr.s_addr = INADDR_ANY;
   bzero(&(server_addr.sin_zero),8);

   //
   if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
   {
      perror("Nao foi possivel realizar o bind");
      exit(1);
   }

   // quantidade de conexões aceitas pelo servidor 
   if (listen(sock, BACKLOG) == -1)
   {
      perror("Erro de Listen");
      exit(1);
   }

   printf("\nServidor TCP esperando por conexoes na porta 7000\n");
   fflush(stdout);


   // Loop para receber varias solicitacoes
   while(1)
   {

      // Variavel para armazenar o tamanho de endereco do cliente conectado
      sin_size = sizeof(struct sockaddr_in);
      
      connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
      printf("\nConexão aceita de (%s , %d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
      
      // criação de threads para a troca de mensagem com o servidor 
      pthread_t thread_id;

      if( pthread_create( &thread_id , NULL , connection_handler , (void*) &sock) < 0)
      {
        perror("could not create thread");
        return 1;
      } 
   }
   return 0;
}


/* uma conexão aberta para cada cliente, através do uso de threads */
void *connection_handler(void *sock){
    // captura o descritor de socket 
    int connected = *(int*) sock;
     char send_data [1024] , recv_data[1024];
     int bytes_recv;

     // Loop para manter a troca de mensagens
      while (1)
      {

         printf("\n Envie (s or S para sair) : ");
         fgets(send_data, 1024, stdin);
         
         // Função send(int socket, void*buffer, size_t size, int flags)
         send(connected, send_data, strlen(send_data), 0);

         sleep(1);

         if (strcmp(send_data,"s\n") == 0 || strcmp(send_data,"S\n") == 0)
         {
            printf("\n Bye...\n");
            fflush(stdout);

            close(connected);
            break;
         }
         else
         {

            // Funcao recv (int socket, void *buffer, size_t size, int flags)        
            bytes_recv = recv(connected, recv_data, 1024, 0);

            recv_data[bytes_recv] = '\0';
               
            if (strcmp(recv_data,"s\n") == 0 || strcmp(recv_data,"S\n") == 0)
            {
               close(connected);
               printf("\nThe Cliente enviou uma mensagem de fechamento de conexao!\n");
               fflush(stdout);
               break;
            }
            else
               printf("\n Mensagem recebida: %s \n" , recv_data);
          }
         
         fflush(stdout);
      }

      //free(sock);
}