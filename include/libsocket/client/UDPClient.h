//
// Created by ivan on 5/23/15.
//

#ifndef ZAVRSNI_UDPCLIENT_H
#define ZAVRSNI_UDPCLIENT_H

#include "Client.h"


class UDPClient : public Client {
public:
    UDPClient(std::string address, std::string port, int ai_family) : Client(address, port, false, ai_family) { }

    static UDPClient createIPv4(std::string address, std::string port) {
        return UDPClient(address, port, AF_INET);
    }

    static UDPClient createIPv6(std::string address, std::string port) {
        return UDPClient(address, port, AF_INET6);
    }


};


#endif //ZAVRSNI_UDPCLIENT_H
