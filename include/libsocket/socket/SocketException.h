//
// Created by ivan on 5/22/15.
//

#ifndef _LIBSOCKET_SOCKETEXCEPTION_H
#define _LIBSOCKET_SOCKETEXCEPTION_H

#include <string>

#include <vector>
#include <mystl/exception.h>
class SocketException:public mystd::exception {
public:

    SocketException(int err_num, std::string const &msg) : mystd::exception(err_num, msg) { }
};

#endif //_LIBSOCKET_SOCKETEXCEPTION_H
