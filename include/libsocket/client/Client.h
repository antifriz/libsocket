//
// Created by ivan on 5/22/15.
//

#ifndef ZAVRSNI_CLIENT_H
#define ZAVRSNI_CLIENT_H

#include <sstream>
#include <stdlib.h>
#include <libsocket/socket/SocketException.h>
#include <libsocket/socket/Socket.h>
#include <mystl/random.h>
#include <unistd.h>

class Client {
public:
    Client(std::string address,std::string port, bool isTCP, int ai_family) try : socket_(
            Socket::create(address.c_str(), port, isTCP, ai_family)),pid_(getpid()) {
        socket_.connect();
    } catch (SocketException &s) {
        s.append_msg("Server::client");
        throw;
    }

    inline ssize_t send(const Bytes &bytes) const {
        return socket().send(bytes);
    }

    inline bool send_all(const Bytes &bytes) const {
        return socket().send_all(bytes);
    }

    inline Bytes recv() const {
        return socket().recv();
    }
    inline int pid(){
        return pid_;
    }


    inline void update_pid(){
        pid_= getpid();
    }

    inline const Socket &socket() const {
        return socket_;
    }

    static std::string generate_random_free_port();

private:
    Socket socket_;
    int pid_;
};


#endif //ZAVRSNI_CLIENT_H
