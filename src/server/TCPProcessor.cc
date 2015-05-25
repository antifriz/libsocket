//
// Created by ivan on 5/23/15.
//
#include <libsocket/server/TCPProcessor.h>
#include <libsocket/server/TCPServer.h>
#include <libsocket/core/network_typedefs.h>
#include <libsocket/socket/SocketAddr.h>


void  TCPProcessor::delegate_request(TCPServer * server,Socket * socket, SocketAddr addr) {
    socket_ = socket;
    server_=server;
    client_ = addr;
    process_request();
}