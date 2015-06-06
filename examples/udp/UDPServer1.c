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
#define NPACK 10
#define PORT 7777

int main(void)
{
   struct sockaddr_in si_me, si_other;
   int s, i, slen=sizeof(si_other);
   char buf[BUFLEN];

   if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
   {
      perror("Erro de socket...");
      exit(-1);
   }
    
   memset((char *) &si_me, 0, sizeof(si_me));
    
   si_me.sin_family = AF_INET;
   si_me.sin_port = htons(PORT);
   si_me.sin_addr.s_addr = htonl(INADDR_ANY);

   if (bind(s, (struct sockaddr *) &si_me, sizeof(si_me))==-1)
   {
      perror("Erro de Bind");
      exit(1);
   }

   for (i=0; i<NPACK; i++) {
   
      if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)==-1)
      {
         perror("Erro de recepcao...");
         exit(1);
      }

      printf("Pacotes recebidos de %s:%d\nData: %s\n\n", 
      inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);

      sleep(1);
   }
   
   close(s);
   return 0;
}
