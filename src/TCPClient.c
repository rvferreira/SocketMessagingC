#include "TCPClient.h"
#include "message.h"

int sockClient;
/* estabelece uma conexão com um servidor online */
int establishedConnection(char ip[])
{
   struct hostent *host;
   struct sockaddr_in server_addr;
     int bytes_recv;
   char reply[1024];

   host = gethostbyname(ip);
   

   /* cria uma variável do tipo sock */
   if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) == -1)
   {
      perror("Error: failed function socket");
      exit(1);
   }

   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(DEFAULT_PORT);
   server_addr.sin_addr = *((struct in_addr *)host->h_addr);
   bzero(&(server_addr.sin_zero),8);

   if (connect(sockClient, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
   {
      perror("Server offline");
      exit(1);
   }

   bytes_recv =  recv(sockClient,reply,1024,0);
   reply[bytes_recv] = '\0';

   printf("\n %s \n",reply);

   getchar();

  return 0;

}

void closeConnectionServer(){

   /* avisa o servidor que fechou a conexão */ 
   send(sockClient,"close",strlen("close"), 0);
   close(sockClient);
}

void sendMessage(ServerMessage m){
   int bytes_recv;
   char reply[1024];
   /* envia mensagem para o servidor */
   if (send(sockClient,m.message,strlen(m.message), 0) == -1) {
      printf("Error: Message \n");
   }

   /*servidor confirma o recebimento da mensagem */
   bytes_recv =  recv(sockClient,reply,1024,0);
   reply[bytes_recv] = '\0';
   printf("\n %s \n",reply);

}
