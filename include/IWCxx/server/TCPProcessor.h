//
// Created by ivan on 5/23/15.
//

#ifndef ZAVRSNI_UDPPROCESSOR_H
#define ZAVRSNI_UDPPROCESSOR_H


#include "TCPServer.h"

class TCPServer;

class TCPProcessor {

public:
    void delegate_request(TCPServer * server, SocketAddr addr);

    TCPServer *server() { return server_; }

    SocketAddr client() const {
        return client_;
    }
protected:

    virtual void process_request() = 0;

private:
    TCPServer * server_;
    SocketAddr client_;
};


#endif //ZAVRSNI_UDPPROCESSOR_H
