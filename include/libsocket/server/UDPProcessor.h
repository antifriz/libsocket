//
// Created by ivan on 5/23/15.
//

#ifndef ZAVRSNI_UDPPROCESSOR_H
#define ZAVRSNI_UDPPROCESSOR_H


#include "UDPServer.h"

class UDPServer;

class UDPProcessor {

public:

    void delegate_request(UDPServer * server, SocketAddr addr, Bytes bytes);

    UDPServer *server() { return server_; }

    SocketAddr client() const {
        return client_;
    }

    Bytes received_bytes() const {
        return received_bytes_;
    }
protected:

    virtual void process_request() = 0;

private:
    UDPServer * server_;
    SocketAddr client_;
    Bytes received_bytes_;


};


#endif //ZAVRSNI_UDPPROCESSOR_H
