#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[ ])
{
   int sock, i;
   char server_name[512];
   struct hostent *host;
   struct sockaddr_in server_addr;

   // O nome do host deve ser informado
   printf("\nDigite o nome do host ou o endereco IP\n");
   scanf("%s", server_name);
   getchar();
   
   host = gethostbyname(server_name);


   for(i = 1; i < 65535; i++)
   {
      
      if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
      {
         perror("Erro de Socket");
         exit(1);
      }

      server_addr.sin_family = AF_INET;
      server_addr.sin_port = htons(i);
      server_addr.sin_addr = *((struct in_addr *)host->h_addr);
      bzero(&(server_addr.sin_zero),8);

      if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) != -1)
      {
         printf("A Porta %d esta aberta!\n", i);      
         fflush(stdout);
      }
      
      close(sock);  
   }
   
   return 0;
}

