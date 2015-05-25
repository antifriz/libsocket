//
// Created by ivan on 5/22/15.
//

#include <libsocket/server/Server.h>

std::string  Server::generate_random_free_port() {
    uint16_t a = mystd::random<uint16_t>(MIN_FREE_PORT,MAX_FREE_PORT);
    std::stringstream ss;
    ss << a;
    return ss.str();
}
