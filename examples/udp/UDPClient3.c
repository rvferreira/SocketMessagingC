/* fpont 12/99 */
/* pont.net    */
/* udpClient.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <sys/time.h> /* select() */ 

#define REMOTE_SERVER_PORT 1500
#define MAX_MSG 100


int main(int argc, char *argv[]) {
  
  int sd, rc, i;
  struct sockaddr_in cliAddr, remoteServAddr;
  struct hostent *h;

  /* Checa argumentos de linha de comando */
  if(argc<3) {
    printf("Uso : %s <servidor> <dado> ... <dadoN> \n", argv[0]);
    exit(1);
  }

  /* Obtem o endereco IP do servidor (nao verifica se a entrada e IP ou nome */
  h = gethostbyname(argv[1]);
  if(h==NULL) {
    printf("%s: Host desconhecido '%s' \n", argv[0], argv[1]);
    exit(1);
  }

  printf("%s: Enviando dado para '%s' (IP : %s) \n", argv[0], h->h_name,
	 inet_ntoa(*(struct in_addr *)h->h_addr_list[0]));

  remoteServAddr.sin_family = h->h_addrtype;
  memcpy((char *) &remoteServAddr.sin_addr.s_addr, 
	 h->h_addr_list[0], h->h_length);
  remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);

  /* Criacao do socket */
  sd = socket(AF_INET,SOCK_DGRAM,0);
  if(sd<0) {
    printf("%s: Nao pode abrir o sockect \n",argv[0]);
    exit(1);
  }
  
  /* Bind para realizar a conexao */
  cliAddr.sin_family = AF_INET;
  cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  cliAddr.sin_port = htons(0);
  
  rc = bind(sd, (struct sockaddr *) &cliAddr, sizeof(cliAddr));
  if(rc<0) {
    printf("%s: Impossivel fazer o bind...\n", argv[0]);
    exit(1);
  }


  /* Envio dos dados */
  for(i=2;i<argc;i++) {
    rc = sendto(sd, argv[i], strlen(argv[i])+1, 0, 
		(struct sockaddr *) &remoteServAddr, 
		sizeof(remoteServAddr));

    if(rc<0) {
      printf("%s: Nao pode enviar dados... %d \n",argv[0],i-1);
      close(sd);
      exit(1);
    }

  }
  
  return 1;

}
