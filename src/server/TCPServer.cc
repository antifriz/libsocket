//
// Created by ivan on 5/23/15.
//

#include <IWCxx/server/TCPServer.h>
#include <mystl/signal_handlers.h>

TCPServer::TCPServer(char *port, int ai_family, int backlog) : Server(port, true, ai_family, backlog) {
}

void TCPServer::await_clients(TCPProcessor * processor) {
        try{
            mystd::reap_dead_processes();
        }
        catch(mystd::signal_handlers_exception &e){
        }
        while (true) {
            try {

                Socket new_socket;
                SocketAddr client;
                this->socket().accept(&new_socket,&client);

                processor->delegate_request(new_socket,client);
            } catch (SocketException &s) {
                s.append_msg("TCPServer::await_clients");
                //std::cout<<s.c_str()<<std::endl;
                exit(s.err_num());
                //throw;
            }
        }
    }