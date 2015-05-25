//
// Created by ivan on 5/23/15.
//

#ifndef _LIBSOCKET_UDPPROCESSOR_H
#define _LIBSOCKET_UDPPROCESSOR_H

#include <libsocket/core/network_typedefs.h>
#include <libsocket/socket/SocketAddr.h>

class UDPServer;

class UDPProcessor {

public:

    void delegate_request(UDPServer * server, SocketAddr addr, Bytes bytes);

    UDPServer *server() { return server_; }

    inline SocketAddr client() const {
        return client_;
    }

    inline Bytes received_bytes() const {
        return received_bytes_;
    }
protected:

    virtual void process_request() = 0;

private:
    UDPServer * server_;
    SocketAddr client_;
    Bytes received_bytes_;


};
#include "UDPServer.h"



#endif //_LIBSOCKET_UDPPROCESSOR_H
