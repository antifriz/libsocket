//
// Created by ivan on 5/21/15.
//

#ifndef _LIBSOCKET_SERIALIZATION_H
#define _LIBSOCKET_SERIALIZATION_H

#include "libsocket/core/network_typedefs.h"

#include <sys/types.h>
#include <inttypes.h>

#define pack754_32(f) (pack754((f), 32, 8))
#define pack754_64(f) (pack754((f), 64, 11))
#define unpack754_32(i) (unpack754((i), 32, 8))
#define unpack754_64(i) (unpack754((i), 64, 11))

// various bits for floating point types--
// varies for different architectures
typedef float float32_t;
typedef double float64_t;


class Serialization {
private:

    static uint64_t pack754(long double f, unsigned bits, unsigned expbits);

    static long double unpack754(uint64_t i, unsigned bits, unsigned expbits);

    static void packi16(unsigned char *buf, unsigned int i);

    static void packi16(Bytes& bytes, unsigned int i);

    static void packi32(unsigned char *buf, unsigned long i);

    static void packi32(Bytes &bytes, unsigned int i);

    static void packi64(unsigned char *buf, uint64_t i);

    static void packi64(Bytes& bytes, unsigned int i);

    static unsigned int unpacki16(unsigned char const *buf);

    static uint32_t unpacki32(unsigned char const *buf);

public:
    static void unpack(const Bytes &bytes, size_t &read_bytes, char const *format, ...);
    static void pack(Bytes & bytes, char const *format, ...);

    static void unpack(unsigned char *buf, size_t & read_bytes, const char *format, ...);
    static void pack(unsigned char *buf, size_t *written_size, char const *format, ...);




};

#endif //_LIBSOCKET_SERIALIZATION_H
