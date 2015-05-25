//
// Created by ivan on 5/23/15.
//
#include <IWCxx/server/TCPProcessor.h>
#include <IWCxx/server/TCPServer.h>
#include <IWCxx/core/network_typedefs.h>
#include <IWCxx/socket/SocketAddr.h>


void  TCPProcessor::delegate_request(TCPServer * server,Socket * socket, SocketAddr addr) {
    socket_ = socket;
    server_=server;
    client_ = addr;
    process_request();
}