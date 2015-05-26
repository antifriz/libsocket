//
// Created by ivan on 5/23/15.
//

#ifndef ZAVRSNI_TCPCLIENT_H
#define ZAVRSNI_TCPCLIENT_H

#include "Client.h"

class TCPClient : public Client {
private:
public:
    TCPClient(std::string address, std::string port, int ai_family) : Client(address, port, true, ai_family) { }

    static TCPClient createIPv4(std::string address, std::string port) {
        return TCPClient(address, port, AF_INET);
    }

    static TCPClient createIPv6(std::string address, std::string port) {
        return TCPClient(address, port, AF_INET6);
    }
};


#endif //ZAVRSNI_TCPCLIENT_H
