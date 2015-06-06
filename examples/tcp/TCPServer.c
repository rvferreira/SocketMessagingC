#include <sys/types.h>   // Definicao de tipos
#include <sys/socket.h>  // Biblioteca de estrutara de sockets
#include <netinet/in.h>  // Define os padroes de protocolo IP
#include <arpa/inet.h>   // Converte enderecos hosts
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Define constantes POSIX
#include <errno.h>  // Utilizado para capturar mensagens de erro

int main(int argc, char *argv[ ])
{
   /*
    Estrutura de um socket

    struct sockaddr_in {
           short int sin_family; -> Familia do endereço do socket: 
		1) AF_INET- ARPA INTERNET  PROTOCOLS
		2) AF_UNIX- UNIX INTERNET PROTOCOLS
		3)AF_ISSO- ISO PROTOCOLS
		4)AF_NS- XEROX NETWORK SYSTEM PROTOCOLS
           
	   unsigned short int sin_port; -> Numero da porta de comunicacao
           struct in_addr sin_addr; -> Endereco IP
           unsigned char sin_zero[8]; -> Zerar a estrutura do socket - nao utilizado
    
     Um socket (AF_INET) pode ter três tipos de estilo: 
	"SOCK_STREAM" (TCP - Stream de Dados - Stream Socket), 
	"SOCK_DGRAM" (UDP - Datagrama - Datagram Sockets) ou 
	"SOCK_RAW" (Baixo Nivel de Rede, normalmente nao utilizado)
   */

   
   //Variaveis
   int sock, connected, bytes_recv, i, true = 1;
   char send_data [1024] , recv_data[1024];
   struct sockaddr_in server_addr, client_addr;
   int sin_size;

   /* Funcao socket(sin_family,socket_type,protocol_number) retorna um inteiro (socket descriptor), caso erro retorna -1
   
      O numero do protocolo (protocol_number) pode ser algum dos seguintes:
   		0 - IP - Internet Protocol (Default)
    		1 - ICMP - Internet Control Message Protocol
    		2 - IGMP - Internet Group Multicast Protocol
    		3 - GGP - Gateway-Gateway Protocol
    		6 - TCP - Transmission Control Protocol
    		17 - UDP - User Datagram Protocol	
   */ 

   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
   {
     perror("Erro no Socket");
     exit(1);
   }

 
   /* Funcao setsockopt(int socket, int level, int optname, void*optval, size_t optlen)
   
	Esta funcao seta o valor (optval) de uma opcao (optname) em um certo nivel (level) de camada de protocolo no socket
	
	int socket = descriptor do socket
   	
	int level = nivel da camada do protocolo (SOL_SOCKET = Constante de nivel para o socket, outros: IPPROTO_IP, IPPROTO_TCP, IPPROTO_UDP)
   	
	int optname = Opcao desejada para a alteracao
   
	optval = valor da opcao
   
	optlen = tamanho do valor

  	Neste exemplo iremos alterar o valor no nivel de socket para a opcao SO_REUSEADDR. Por default um socket criado aceita apenas
   	uma conexao por endereco, ou seja o valor de SO_REUSEADDR é igual FALSE (0). Para alterar esse valor e permitirmos que o
   	mesmo endereco possa receber varias conexoes devemos alterar o valor da opcao SO_REUSEADDR para TRUE (1).

   */

   if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &true,sizeof(int)) == -1)
   {
      perror("Erro Setsockopt");
      exit(1);
   }


   // Configura o endereco de destino
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(7000);
   server_addr.sin_addr.s_addr = INADDR_ANY;
   bzero(&(server_addr.sin_zero),8);


   /* Uma vez com o socket criado precisamos informar o endereço ao socket. Para isso utilizamos a funcao bind
   
	Funcao bind(int socket, struct sockaddr*addr, size_t length)

   	int socket = descriptor do socket

   	struct sockaddr*addr = endereco de destino

   	size_t length = tamanho do endereco

   	A funcao bind retorna 0 em caso de sucesso e -1 em caso de erro
   */

   if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
   {
      perror("Nao foi possivel realizar o bind");
      exit(1);
   }


   /* Como estamos criando um servidor que ira receber solicitacoes este socket deve ficar "ouvindo" (aguardando conexoes) na
      porta especificada. A funcao listen realiza essa tarefa.

   	Funcao listen(int socket, unsigned int n) onde;
   	
	int socket = descriptor do socket

   	unsigned int n = tamanho da fila de conexoes pendentes
   
   	Obs: Quando utilizamos o listen devemos utilizar a funcao accept que veremos mais adiante no codigo

   */

   if (listen(sock, 10) == -1)
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

      /* Funcao accept(int socket, struct sockaddr*addr, size_t*length_ptr)
	A funcao accept aceita uma conexao e cria um novo socket para esta conexao
      	
	int socket = descriptor do socket
      
	struct sockaddr*addr = endereco de destino (cliente)
      
	size_t*length_ptr = tamanho do endereco de destino

      	Obs: A funcao accept por padrão fica aguardando a chegada de um pedido de conexao. Para que ela nao fique, devemos
      	configurar o socket no modo sem bloqueio (nonblocking mode set). Neste exemplo ficaremos com o modo padrao (bloqueante)

      	A funcao accept retorna  

      */
      
      connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
      printf("\nConexão aceita de (%s , %d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
   
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
   }
   
   close(sock);
   return 0;
}
