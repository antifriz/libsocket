//
// Created by ivan on 5/22/15.
//

#ifndef ZAVRSNI_SOCKET_H
#define ZAVRSNI_SOCKET_H
// Definition of the Socket class



#include <string>
#include <IWCxx/core/network_typedefs.h>
#include "SocketAddr.h"

#define MAX_BUFFER_SIZE 1000


class Socket {
public:
    Socket(int sockfd, const SocketAddr &socket_addr) : sockfd_(sockfd), socket_addr_(socket_addr) { }
    Socket(int sockfd) : sockfd_(sockfd) { }

    virtual ~Socket();


    static Socket fill_from_addrinfo(struct addrinfo *obj);

    static Socket create(const char * address, std::string port, bool isTCP, int ai_family);

    static int socket(int domain, int type, int protocol);

    void close() const;

    void bind();

    void listen(int backlog);

    void accept(Socket * new_socket, SocketAddr * client);


    void connect(const SocketAddr & sadr) const;


    ssize_t send(const Bytes &bytes) const;

    bool sendAll(const Bytes &bytes) const;

    ssize_t send_to(const Bytes &bytes, const SocketAddr &client) const;

    Bytes recv() const;


    Bytes recv_from(SocketAddr &client) const;

    bool can_read(long max_wait_sec=0, long max_wait_usec=0) const;

    void allow_reuse_address();

    //void set_non_blocking(const bool);

    //bool is_valid() const { return sockfd_ != -1; }

    int sockfd() const {return sockfd_;}

private:
    int sockfd_;
    SocketAddr socket_addr_;

};



#endif //ZAVRSNI_SOCKET_H
