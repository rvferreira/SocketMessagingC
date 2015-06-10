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
/*
  O código do socket foi baseado no disponibilizado pelo site da
  disciplina "moodle.lasdpc.icmc.usp.br"
*/


void runServer(){
  
  //Variáveis
  int sock, connected, bytes_recv, iTrue = 1;
  char send_data [1024] , recv_data[1024];
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


   if (listen(sock, 10) == -1)
   {
      perror("Error: failed function listen");
       exit(1);
   }
   
   /* servidor fica ouvindo as requisições dos clientes */
     printf("\nServer TCP waiting for connections in port 7000... \n");
    fflush(stdout);


     strcpy(send_data,"Your Successful Connection!");


   while(1){
      
         // Variavel para armazenar o tamanho de endereco do cliente conectado
        sin_size = sizeof(struct sockaddr_in);

         //aceita a nova conexão
         connected = accept(sock, (struct sockaddr *)&client_addr, (socklen_t*) &sin_size);
         
         
          printf("\nConexão aceita de (%s , %d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
          
              
      // Loop para manter a troca de mensagens
      while (1){

         // Função send(int socket, void*buffer, size_t size, int flags)
         send(connected, send_data, strlen(send_data), 0);

         sleep(1);

         

            // Funcao recv (int socket, void *buffer, size_t size, int flags)        
            bytes_recv = recv(connected, recv_data, 1024, 0);
            recv_data[bytes_recv] = '\0';
           
               
            if (strcmp(recv_data,"close") == 0 && bytes_recv)
            {
               close(connected);
               printf("\nLost connection... \n");
               fflush(stdout);
               break;
            }
            else {
               printf("\n Message received: %s \n" , recv_data);
               strcpy(send_data,"Your message was sent successfully!");
           }
         
            fflush(stdout);
        }
     }     
   
   close(sock);

}
