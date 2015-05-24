//
// Created by ivan on 5/23/15.
//

#include <IWCxx/server/TCPServer.h>

TCPServer::TCPServer(char *port, int ai_family, int backlog) : Server(port, true, ai_family, backlog) {
}