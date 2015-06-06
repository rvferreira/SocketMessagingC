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
   int sock, bytes_recv, i;
   char send_data[1024],recv_data[1024],server_name[512];
   struct hostent *host;
   struct sockaddr_in server_addr;

   // O nome do servidor (host) deve ser informado
   printf("\n Digite o nome ou o endereco IP do servidor\n");
   scanf("%s", server_name);
   getchar();
   
   host = gethostbyname(server_name);
   
   
   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
   {
      perror("Erro de Socket");
      exit(1);
   }

   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(7000);
   server_addr.sin_addr = *((struct in_addr *)host->h_addr);
   bzero(&(server_addr.sin_zero),8);

   if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
   {
      perror("Erro de conexao");
      exit(1);
   }

   while(1)
   {

      sleep(1);

      bytes_recv=recv(sock,recv_data,1024,0);
      recv_data[bytes_recv] = '\0';
      
      if (strcmp(recv_data,"q\n") == 0 || strcmp(recv_data,"Q\n") == 0)
      {
         printf("\nSevidor enviou uma mensagem de fechamento de conexao!\n");
         fflush(stdout);
         close(sock);
         break;
      }
      else
         printf("\nMensagem recebida:  %s \n" , recv_data);

    
      printf("\n Envie (s or S para sair) : ");
      fflush(stdout);
      fgets(send_data, 1024, stdin);
      
            
      if (strcmp(send_data,"s\n") != 0 && strcmp(send_data,"S\n") != 0)
         send(sock,send_data,strlen(send_data), 0);
      else
      {
         printf("\nBye...\n");
         fflush(stdout);
         send(sock,send_data,strlen(send_data), 0);
         close(sock);
         break;
      }

   }

   return 0;

}

