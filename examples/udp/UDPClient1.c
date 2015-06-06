#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define BUFLEN 1024
#define NAME 512
#define NPACK 10
#define PORT 7777

int main(void)
{
   struct sockaddr_in si_other;
   int s, i, slen=sizeof(si_other);
   char buf[BUFLEN],server_name[NAME];
   struct hostent *host;

   // O nome do servidor (host) deve ser informado
   printf("\nDigite o nome do servidor ou o endereco IP\n");
   scanf("%s", server_name);
   getchar();
   
   host = gethostbyname(server_name);

   // Para UDP utilizamos SOCK_DGRAM
   if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
   {
      perror("Erro de Socket");
      exit(1);
   }

   memset((char *) &si_other, 0, sizeof(si_other));
   
   si_other.sin_family = AF_INET;
   si_other.sin_port = htons(PORT);
   si_other.sin_addr = *((struct in_addr *)host->h_addr);
   
   // Enviando 10 pacotes
   for (i=0; i<NPACK; i++) {
      printf("Enviando pacote %d\n", i);
      sprintf(buf, "Este e o pacote %d\n", i);
      if (sendto(s, buf, BUFLEN, 0,(struct sockaddr *)  &si_other, slen)==-1)
      {
         perror("Erro no envio do pacote...");
         exit(1);
      }

      sleep(2);
   }
   
   close(s);
   return 0;
}
