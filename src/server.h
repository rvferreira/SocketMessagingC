/*
 * server.h
 *
 *  Created on: Jun 6, 2015
 *      Author: rferreira
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/types.h>   // Definicao de tipos
#include <sys/socket.h>  // Biblioteca de estrutara de sockets
#include <netinet/in.h>  // Define os padroes de protocolo IP
#include <arpa/inet.h>   // Converte enderecos hosts
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Define constantes POSIX
#include <errno.h>  // Utilizado para capturar mensagens de erro

int runServer();

#endif /* SERVER_H_ */
