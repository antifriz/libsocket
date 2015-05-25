//
// Created by ivan on 5/23/15.
//

#ifndef ZAVRSNI_TCPPROCESSOR_H
#define ZAVRSNI_TCPPROCESSOR_H


#include <IWCxx/socket/Socket.h>
class TCPServer;

class TCPProcessor {

public:
    void delegate_request(TCPServer *server, Socket *socket, SocketAddr addr);

    inline Socket *socket() { return socket_; }

    inline TCPServer *server() { return server_; }

    inline SocketAddr client() const { return client_; }

protected:

    virtual void process_request() = 0;

private:
    Socket *socket_;
    TCPServer *server_;
    SocketAddr client_;
};
#include "TCPServer.h"


#endif //ZAVRSNI_UDPPROCESSOR_H
