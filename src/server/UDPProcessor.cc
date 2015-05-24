//
// Created by ivan on 5/23/15.
//
#include <IWCxx/server/UDPProcessor.h>
#include <IWCxx/server/UDPServer.h>
#include <IWCxx/core/network_typedefs.h>
#include <IWCxx/socket/SocketAddr.h>


void  UDPProcessor::delegate_request(UDPServer * server, SocketAddr addr, Bytes bytes) {
    server_ = server;
    client_ = addr;
    received_bytes_ = bytes;
    process_request();
}