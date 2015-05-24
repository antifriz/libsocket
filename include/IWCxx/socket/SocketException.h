//
// Created by ivan on 5/22/15.
//

#ifndef ZAVRSNI_SOCKETEXCEPTION_H
#define ZAVRSNI_SOCKETEXCEPTION_H

#include <string>

#include <vector>
#include <mystl/exception.h>
class SocketException:public mystd::exception {
public:

    SocketException(int err_num, std::string const &msg) : mystd::exception(err_num, msg) { }
};

#endif //ZAVRSNI_SOCKETEXCEPTION_H
