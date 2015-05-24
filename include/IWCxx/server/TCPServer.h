//
// Created by ivan on 5/23/15.
//

#ifndef ZAVRSNI_TCPSERVER_H
#define ZAVRSNI_TCPSERVER_H

#include "Server.h"

class TCPServer : public Server {
private:
public:
    TCPServer(char *port, int ai_family, int backlog);


};


#endif //ZAVRSNI_TCPSERVER_H
