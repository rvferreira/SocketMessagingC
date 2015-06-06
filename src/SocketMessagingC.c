/*
 ============================================================================
 Name        : SocketMessagingC.c
 Author      : Raphael Ferreira e Jéssika Darambaris
 Version     : 1.0
 Copyright   : Use a vontz, mas conserve os créditos
 Description : Server-Client message passing in C, Ansi-style
 ============================================================================
 */

#define PROGRAM_NAME "SocketMessagingC"

#define USAGE "\
Usage: " PROGRAM_NAME " [options] IP\n\
Try \"" PROGRAM_NAME " --help\" for more informations.\n"

#define HELP "\
Usage: " PROGRAM_NAME " [ServerIP] [options] \n\n\
Client example: ./" PROGRAM_NAME " 127.0.0.1\n\
	\tRuns a client program that will connect to a local server\n\
Server example: ./" PROGRAM_NAME " --server\n\
	\tRuns a server that will be waiting for connections\n\
\n\
Emulation Options:\n\
  --server    		runs in server mode\n\
  --debug    		turn on debug prints\n\
\n\
Fun fact: You killed the fun.\n"

#define SERVER_MODE "\
Starting " PROGRAM_NAME " in Server Mode. \n\
All chat functions will be disabled.\n"

#define BAD_OPTION   "Bad option: "
#define NO_VALID_IP "Invalid IPv4 address: "

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"
#include "client.h"
#include "utils.h"

int processInput(int argc, char** argv, char **option, char **ip);

int serverMode = 0;		// Global variable that defines whether this is a Client or a Server

int main(int argc, char *argv[]) {
	char *option = NULL;
	char *ip = NULL;

	if (processInput(argc, argv, &option, &ip)) {
		printf("%s \n",USAGE);
		return EXIT_FAILURE;
	}

	if (!serverMode) {
		printf("Trying to reach server at %s:%d \n", ip, DEFAULT_PORT);
		runClient();
	}

	return EXIT_SUCCESS;
}

int processInput(int argc, char** argv, char **option, char **ip) {
	*ip = malloc(15*sizeof(char));
	*option = malloc(15*sizeof(char));

    if (argc > 1) {
        *ip = argv[1];

        if (argv[1][0] == '-') {
    		*option = argv[1];
    	}

    }
    if (argc > 2) {
        *option = argv[2];

        if (argv[1][0] == '-') {
			*option = argv[1];
			*ip = argv[2];
		}
    }

    if (argc < 2 || argc > 3) {
        return 1;
    }

    if (!strcmp(*option, "--help")) {
        printf("%s\n", HELP);
        exit(1);
    }

    if (!strcmp(*option, "--server")) {
    	if (argc > 2) {
			printf("%s\n", HELP);
			exit(1);
		}
		printf("%s\n", SERVER_MODE);
		serverMode = 1;
	}

    return 0;
}
