//
// Created by ivan on 5/22/15.
//

#include <libsocket/socket/Getaddrinfo.h>
#include <libsocket/socket/SocketException.h>
#include <assert.h>

Getaddrinfo  Getaddrinfo::from_hints(int ai_family, int ai_socktype, int ai_flags) {
        struct addrinfo hints;
        memset(&hints, 0, sizeof hints);
        hints.ai_family = ai_family;
        hints.ai_socktype = ai_socktype;
        hints.ai_flags = ai_flags;
        return Getaddrinfo(hints);
}

struct addrinfo *Getaddrinfo::next() {
        if(!is_valid)
                throw SocketException(-1, "Getaddrinfo::next");
        struct addrinfo *addrinfo_p1 = addrinfo_p;
        addrinfo_p = addrinfo_p->ai_next;
        return addrinfo_p1;
}

void Getaddrinfo::run(const char *  address, const std::string service) {
        is_valid = false;
        int rv = ::getaddrinfo(address, service.c_str(), &hints, &addrinfo_all);
        addrinfo_p = addrinfo_all;
        if (rv != 0)
                throw SocketException(-1, "Getaddrinfo::run");
        is_valid = true;
}

bool Getaddrinfo::has_next() {
        if(!is_valid)
                throw SocketException(-1, "Getaddrinfo::has_next");
        return addrinfo_p != NULL;
}

void Getaddrinfo::free() {
        freeaddrinfo(addrinfo_all);
}

 Getaddrinfo::~Getaddrinfo() {
        if (is_valid && has_next())
                free();
}