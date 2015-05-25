//
// Created by ivan on 5/23/15.
//


#ifndef _LIBSOCKET_SERIALIZATIONEXCEPTION_H
#define _LIBSOCKET_SERIALIZATIONEXCEPTION_H
#include <mystl/exception.h>

class SerializationException:public mystd::exception{
public:
    SerializationException(int err_num, std::string const &msg) : mystd::exception(err_num, msg) { }

};

#endif //_LIBSOCKET_SERIALIZATIONEXCEPTION_H
