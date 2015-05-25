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

    static TCPServer createIPv4(std::string port) {
        return TCPServer(port, AF_INET);
    }

    static TCPServer createIPv6(std::string port) {
        return TCPServer(port, AF_INET6);
    }

    void await_clients(TCPProcessor * processor);

};


#endif //ZAVRSNI_TCPSERVER_H
