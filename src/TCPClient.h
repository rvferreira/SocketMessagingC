#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include "utils.h"
#include "message.h"

int establishedConnection(char *);
void closeConnectionServer();
void sendMessage(ServerMessage);

#endif /* TCPCLIENT_H_ */