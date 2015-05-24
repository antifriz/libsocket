//
// Created by ivan on 5/23/15.
//

#ifndef ZAVRSNI_UDPSERVER_H
#define ZAVRSNI_UDPSERVER_H

#include <memory>
#include <string>
#include "Server.h"
#include "UDPProcessor.h"

class UDPProcessor;
class UDPServer : public Server {
public:
    static UDPServer createIPv4(std::string port) {
        return UDPServer(port, AF_INET);
    }

    static UDPServer createIPv6(std::string port) {
        return UDPServer(port, AF_INET6);
    }

    static UDPServer createIPv4RandomPort() {
        return createIPv4(Server::generate_random_free_port());
    }

    static UDPServer createIPv6RandomPort() {
        return createIPv6(Server::generate_random_free_port());
    }

    UDPServer(std::string port, int ai_family);

    void await_clients(UDPProcessor * processor);

};


#endif //ZAVRSNI_UDPSERVER_H
