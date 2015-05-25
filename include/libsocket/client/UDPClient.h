//
// Created by ivan on 5/23/15.
//

#ifndef ZAVRSNI_UDPSERVER_H
#define ZAVRSNI_UDPSERVER_H

#include "Client.h"


class TCPClient : public Client {
public:
    TCPClient(std::string address, std::string port, int ai_family) : Client(address, port, false, ai_family) { }

    static TCPClient createIPv4(std::string address, std::string port) {
        return TCPClient(address, port, AF_INET);
    }

    static TCPClient createIPv6(std::string address, std::string port) {
        return TCPClient(address, port, AF_INET6);
    }


};


#endif //ZAVRSNI_UDPSERVER_H
