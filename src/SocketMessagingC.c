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

/* descrição do menu do programa */
#define USAGE "\
Usage: " PROGRAM_NAME " [options] \n\
Try \"" PROGRAM_NAME " --help\" for more informations.\n"

#define HELP "\
Usage: " PROGRAM_NAME " [options] \n\n\
Client example: ./" PROGRAM_NAME " \n\
\n\
Emulation Options:\n\
  --debug    		turn on debug prints\n\
\n\
Fun fact: You killed the fun.\n"

#define SERVER_MODE "\
Starting " PROGRAM_NAME " in Server Mode. \n"
 /* All chat functions will be disabled.\n" */

#define BAD_OPTION   "Bad option: "
#define NO_VALID_IP "Invalid IPv4 address: "

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"
#include "client.h"

int processInput(int argc, char** argv, char **option);


int main(int argc, char *argv[]) {
	char *option = NULL;

	if (processInput(argc, argv, &option)) {
		printf("%s \n",USAGE);
		return EXIT_FAILURE;
	}

	pthread_t serv;
	if(pthread_create( &serv , NULL , runServer , (void*) 0) < 0) {
		perror("could not create thread");
		exit(1);
	}

	runClient();

	return EXIT_SUCCESS;
}

/* trata a entrada pelos parâmetros passados na execução da entrada */
int processInput(int argc, char** argv, char **option) {
	*option = malloc(15*sizeof(char));

    if (argc > 1) {
		if (argv[1][0] == '-') {
			*option = argv[1];
		}
    }

    /* opção de debug */
    if (!strcmp(*option, "--debug")) {
    	printf("%s\n", "Verbose on.\n");
		debugMode = 1;
	}

	/* opção help que mostra como usar o programa */
    if (!strcmp(*option, "--help")) {
        printf("%s\n", HELP);
        exit(1);
    }

    return 0;
}
