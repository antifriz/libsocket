//
// Created by ivan on 5/23/15.
//

#include <libsocket/socket/SocketAddr.h>
#include <string.h>
#include <arpa/inet.h>

void SocketAddr::assign(struct sockaddr *sas, socklen_t saslen) {
    memcpy(this->sockaddr_ptr(), sas, saslen);
    this->saslen_ = saslen;
}

std::string SocketAddr::get_ip() const {
    return get_ip(sas());
}

in_port_t SocketAddr::get_port() const{
    return get_port(sas());
}


