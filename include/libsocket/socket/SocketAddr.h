//
// Created by ivan on 5/23/15.
//

#ifndef ZAVRSNI_SOCKETADDR_H
#define ZAVRSNI_SOCKETADDR_H

#include <string>

#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

class SocketAddr {
public:
    SocketAddr() { }

    SocketAddr(struct sockaddr_storage const &sas, socklen_t saslen) : sas_(sas), saslen_(saslen) { }

    SocketAddr(struct sockaddr *sas, socklen_t saslen) {
        assign(sas, saslen);
    }

    void assign(struct sockaddr *sas, socklen_t saslen);

    void assign(const struct sockaddr_storage & sas, socklen_t saslen) {
        this->sas_ = sas;
        this->saslen_ = saslen;
    }

    sockaddr_storage const &sas() const {
        return sas_;
    }

    sockaddr *sockaddr_ptr() const {
        return (sockaddr *) &sas_;
    }

    socklen_t saslen() const {
        return saslen_;
    }


    static uint16_t get_port(const struct sockaddr_storage & sas){
        if (sas.ss_family == AF_INET) {
            return ntohs(((struct sockaddr_in*)&sas)->sin_port);
        }

        return ntohs(((struct sockaddr_in6*)&sas)->sin6_port);
    }
    static std::string get_ip(const struct sockaddr_storage & sas)  {
        char buf[INET6_ADDRSTRLEN];
        inet_ntop(sas.ss_family, get_in_addr(sas),buf, sizeof buf);
        return std::string(buf);
    }


    std::string get_ip() const;

    in_port_t get_port() const;


private:
    struct sockaddr_storage sas_;
    socklen_t saslen_;

    static void * get_in_addr(const struct sockaddr_storage & sas){
        if (sas.ss_family == AF_INET) {
            return &(((struct sockaddr_in*)&sas)->sin_addr);
        }

        return &(((struct sockaddr_in6*)&sas)->sin6_addr);
    }

};


#endif //ZAVRSNI_SOCKETADDR_H
