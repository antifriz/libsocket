//
// Created by ivan on 5/22/15.
//

#ifndef ZAVRSNI_SERVER_H
#define ZAVRSNI_SERVER_H

#include <sstream>
#include <stdlib.h>
#include <libsocket/socket/SocketException.h>
#include <libsocket/socket/Socket.h>
#include <mystl/random.h>

#define MAX_FREE_PORT 65535
#define MIN_FREE_PORT 1024

class Server {
public:
    Server(std::string port, bool isTCP, int ai_family, int backlog) try : socket_(
            Socket::create(NULL, port, isTCP, ai_family)) {
        socket_.bind();
        if (isTCP) socket_.listen(backlog);
    } catch (SocketException &s) {
        s.append_msg("Server::server");
        throw;
    }

    ssize_t send(const Bytes &bytes) const {
        return socket().send(bytes);
    }

    bool sendAll(const Bytes &bytes) const {
        return socket().sendAll(bytes);
    }

    Bytes recv() const {
        return socket().recv();
    }



    const Socket &socket() const {
        return socket_;
    }

    static std::string generate_random_free_port() {
        uint16_t a = mystd::random<uint16_t>(MIN_FREE_PORT,MAX_FREE_PORT);
        std::stringstream ss;
        ss << a;
        return ss.str();
    }

private:
    Socket socket_;

};


#endif //ZAVRSNI_SERVER_H
