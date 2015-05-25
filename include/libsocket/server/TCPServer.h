//
// Created by ivan on 5/23/15.
//

#ifndef _LIBSOCKET_TCPSERVER_H
#define _LIBSOCKET_TCPSERVER_H

#include "Server.h"

class TCPProcessor;

class TCPServer : public Server {
private:
public:
    TCPServer(std::string port, int ai_family, int backlog);

    static TCPServer createIPv4(std::string port,int backlog) {
        return TCPServer(port, AF_INET,backlog);
    }

    static TCPServer createIPv6(std::string port,int backlog) {
        return TCPServer(port, AF_INET6,backlog);
    }

    void await_clients(TCPProcessor * processor);



};
#include "TCPProcessor.h"


#endif //_LIBSOCKET_TCPSERVER_H
