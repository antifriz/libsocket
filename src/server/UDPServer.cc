//
// Created by ivan on 5/23/15.
//

#include "IWCxx/server/UDPServer.h"
#include <IWCxx/server/UDPProcessor.h>

#include <IWCxx/core/network_typedefs.h>
#include <IWCxx/socket/SocketAddr.h>
#include <IWCxx/socket/SocketException.h>
#include <IWCxx/server/Server.h>
#include <iostream>


void UDPServer::await_clients(UDPProcessor * processor) {
    while (true) {
        try {
            SocketAddr client;
            //std::cout<<"waiting client"<<std::endl;
            Bytes bytes = this->socket().recv_from(client);


            //std::cout<<"connecting to client "<<client.get_ip()<<"::"<<client.get_port()<<std::endl;

            //std::cout<<"connected to client "<<client.get_ip()<<"::"<<client.get_port()<<std::endl;

            processor->delegate_request(this, client, bytes);
        } catch (SocketException &s) {
            s.append_msg("UDPServer::await_clients");
            //std::cout<<"NOOO"<<std::endl;;

            //std::cout<<s.c_str()<<std::endl;
            exit(s.err_num());
            //throw;
        }
    }
}

UDPServer::UDPServer(std::string port, int ai_family) : Server(Server(port, false, ai_family, 0)) {
}