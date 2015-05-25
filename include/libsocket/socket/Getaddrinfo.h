//
// Created by ivan on 5/22/15.
//

#ifndef _LIBSOCKET_GETADDRINFO_H
#define _LIBSOCKET_GETADDRINFO_H

#include <string.h>
#include <netdb.h>
#include <string>

class Getaddrinfo {
public:
    virtual ~Getaddrinfo();

    static Getaddrinfo from_hints(int ai_family, int ai_socktype, int ai_flags);

    Getaddrinfo(struct addrinfo const &hints) : hints(hints),is_valid(false) { }

    void run(const char *address, const std::string service);

    bool has_next();

    struct addrinfo *next();

    void free();

private:
    struct addrinfo hints;
    struct addrinfo *addrinfo_all, *addrinfo_p;
    bool is_valid;
};

#endif //_LIBSOCKET_GETADDRINFO_H
