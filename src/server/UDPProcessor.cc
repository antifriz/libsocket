//
// Created by ivan on 5/23/15.
//
#include <libsocket/server/UDPProcessor.h>
#include <libsocket/server/UDPServer.h>
#include <libsocket/core/network_typedefs.h>
#include <libsocket/socket/SocketAddr.h>


void  UDPProcessor::delegate_request(UDPServer * server, SocketAddr addr, Bytes bytes) {
    server_ = server;
    client_ = addr;
    received_bytes_ = bytes;
    process_request();
}