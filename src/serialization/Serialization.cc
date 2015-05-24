//
// Created by ivan on 5/21/15.
//
#include "libsocket/serialization/Serialization.h"
#include <assert.h>

#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#include <vector>
#include <string>
#include <libsocket/serialization/SerializationException.h>
#include <algorithm>
void Serialization::pack(Bytes& bytes, const char *format, ...) {
    va_list ap;
    int16_t h;
    int32_t l;
    int8_t c;
    float32_t f;
    char *s;
    int32_t size = 0, len;

    va_start(ap, format);

    for (; *format != '\0'; format++) {
        switch (*format) {
            case 'h': // 16-bit
                size += 2;
                h = (int16_t) va_arg(ap, int); // promoted
                packi16(bytes, h);
                break;

            case 'l': // 32-bit
                size += 4;
                l = va_arg(ap, int32_t);
                packi32(bytes, l);
                break;

            case 'L': // 64-bit
                size += 8;
                l = va_arg(ap, int64_t);
                packi64(bytes, l);
                break;


            case 'c': // 8-bit
                size += 1;
                c = (int8_t) va_arg(ap, int); // promoted
                bytes.push_back((uint8_t) c);
                break;

            case 'f': // float
                size += 4;
                f = (float32_t) va_arg(ap, double); // promoted
                l = pack754_32(f); // convert to IEEE 754
                packi32(bytes, l);
                break;

            case 's': // string
                s = va_arg(ap, char *);
                len = strlen(s);
                bytes.insert(bytes.end(),s,s+len+1);
                break;
            default:
                assert(-1);
        }
    }

    va_end(ap);
}


void Serialization::pack(unsigned char *buf,size_t * written_size, const char *format, ...) {
    va_list ap;
    int16_t h;
    int32_t l;
    int8_t c;
    float32_t f;
    char *s;
    int32_t size = 0, len;

    va_start(ap, format);

    for (; *format != '\0'; format++) {
        switch (*format) {
            case 'h': // 16-bit
                size += 2;
                h = (int16_t) va_arg(ap, int); // promoted
                packi16(buf, h);
                buf += 2;
                break;

            case 'l': // 32-bit
                size += 4;
                l = va_arg(ap, int32_t);
                packi32(buf, l);
                buf += 4;
                break;

            case 'L': // 64-bit
                size += 8;
                l = va_arg(ap, int64_t);
                packi64(buf, l);
                buf += 8;
                break;


            case 'c': // 8-bit
                size += 1;
                c = (int8_t) va_arg(ap, int); // promoted
                *buf++ = (c >> 0) & 0xff;
                break;

            case 'f': // float
                size += 4;
                f = (float32_t) va_arg(ap, double); // promoted
                l = pack754_32(f); // convert to IEEE 754
                packi32(buf, l);
                buf += 4;
                break;

            case 's': // string
                s = va_arg(ap, char*);
                len = strlen(s);
                size += len + 2;
                packi16(buf, len);
                buf += 2;
                memcpy(buf, s, len);
                buf += len;
                break;
            default:
                assert(-1);
        }
    }

    va_end(ap);

    *written_size= size;
}

void Serialization::unpack(const Bytes &bytes, size_t & read_bytes, const char *format, ...) {
    va_list ap;
    int16_t *h;
    int32_t *l;
    int32_t pf;
    int8_t *c;
    float32_t *f;
    char *s;
    int32_t maxstrlen = 0;

    size_t len;

    size_t size = 0;
    va_start(ap, format);

    for (; *format != '\0'; format++) {
        switch (*format) {
            case 'h': // 16-bit
                h = va_arg(ap, int16_t*);
                if(size+2>bytes.size())
                    throw SerializationException(-1,"16-bit");
                *h = unpacki16(bytes.data()+size);
                size += 2;
                break;

            case 'l': // 32-bit
                l = va_arg(ap, int32_t*);

                if(size+4>bytes.size())
                    throw SerializationException(-1,"32-bit");
                *l = unpacki32(bytes.data()+size);
                size += 4;
                break;

            case 'c': // 8-bit
                c = va_arg(ap, int8_t*);

                if(size+1>bytes.size())
                    throw SerializationException(-1,"8-bit");
                *c = *(bytes.data()+size);
                size+=1;
                break;

            case 'f': // float
                f = va_arg(ap, float32_t *);
                if(size+4>bytes.size())
                    throw SerializationException(-1,"32-bit");
                pf = unpacki32(bytes.data()+size);
                size += 4;
                *f = unpack754_32(pf);
                break;

            case 's': // string
                s = va_arg(ap, char*);
                if(std::find(bytes.begin()+size,bytes.end(),'\0') == bytes.end())
                    throw SerializationException(-1,"string");
                len =  strlen((char const *) (bytes.data()+size))+1;
                memcpy(s, bytes.data()+size,len);
                size +=  len;
                break;

            default:
                if (isdigit(*format)) { // track max str len
                    maxstrlen = maxstrlen * 10 + (*format - '0');
                }
        }

        if (!isdigit(*format)) maxstrlen = 0;
    }

    va_end(ap);

    read_bytes = size;
}

void Serialization::unpack(unsigned char *buf, size_t & read_bytes, const char *format, ...) {
    va_list ap;
    int16_t *h;
    int32_t *l;
    int32_t pf;
    int8_t *c;
    float32_t *f;
    char *s;
    int32_t len, count, maxstrlen = 0;
    unsigned char * buf_start = buf;
    va_start(ap, format);

    for (; *format != '\0'; format++) {
        switch (*format) {
            case 'h': // 16-bit
                h = va_arg(ap, int16_t*);
                *h = unpacki16(buf);
                buf += 2;
                break;

            case 'l': // 32-bit
                l = va_arg(ap, int32_t*);
                *l = unpacki32(buf);
                buf += 4;
                break;

            case 'c': // 8-bit
                c = va_arg(ap, int8_t*);
                *c = *buf++;
                break;

            case 'f': // float
                f = va_arg(ap, float32_t *);
                pf = unpacki32(buf);
                buf += 4;
                *f = unpack754_32(pf);
                break;

            case 's': // string
                s = va_arg(ap, char*);
                len = unpacki16(buf);
                buf += 2;
                if (maxstrlen > 0 && len > maxstrlen) count = maxstrlen - 1; else count = len;
                memcpy(s, buf, count);
                s[count] = '\0';
                buf += len;
                break;

            default:
                if (isdigit(*format)) { // track max str len
                    maxstrlen = maxstrlen * 10 + (*format - '0');
                }
        }

        if (!isdigit(*format)) maxstrlen = 0;
    }

    va_end(ap);

    read_bytes = buf - buf_start;
}

uint64_t Serialization::pack754(long double f, unsigned bits, unsigned expbits) {
    long double fnorm;
    int shift;
    long long sign, exp, significand;
    unsigned significandbits = bits - expbits - 1; // -1 for sign bit

    if (f == 0.0) return 0; // get this special case out of the way

    // check sign and begin normalization
    if (f < 0) {
        sign = 1;
        fnorm = -f;
    } else {
        sign = 0;
        fnorm = f;
    }

    // get the normalized form of f and track the exponent
    shift = 0;
    while (fnorm >= 2.0) {
        fnorm /= 2.0;
        shift++;
    }
    while (fnorm < 1.0) {
        fnorm *= 2.0;
        shift--;
    }
    fnorm = fnorm - 1.0;

    // calculate the binary form (non-float) of the significand data
    significand = fnorm * ((1LL << significandbits) + 0.5f);

    // get the biased exponent
    exp = shift + ((1 << (expbits - 1)) - 1); // shift + bias

    // return the final answer
    return (sign << (bits - 1)) | (exp << (bits - expbits - 1)) | significand;
}

long double Serialization::unpack754(uint64_t i, unsigned bits, unsigned expbits) {
    long double result;
    long long shift;
    unsigned bias;
    unsigned significandbits = bits - expbits - 1; // -1 for sign bit

    if (i == 0) return 0.0;

    // pull the significand
    result = (i & ((1LL << significandbits) - 1)); // mask
    result /= (1LL << significandbits); // convert back to float
    result += 1.0f; // add the one back on

    // deal with the exponent
    bias = (1 << (expbits - 1)) - 1;
    shift = ((i >> significandbits) & ((1LL << expbits) - 1)) - bias;
    while (shift > 0) {
        result *= 2.0;
        shift--;
    }
    while (shift < 0) {
        result /= 2.0;
        shift++;
    }

    // sign it
    result *= (i >> (bits - 1)) & 1 ? -1.0 : 1.0;

    return result;
}

void Serialization::packi16(unsigned char *buf, unsigned int i) {
    *buf++ = i >> 8;
    *buf++ = i;
}

void Serialization::packi32(unsigned char *buf, unsigned long i) {
    *buf++ = i >> 24;
    *buf++ = i >> 16;
    *buf++ = i >> 8;
    *buf++ = i;
}
void Serialization::packi64(unsigned char *buf, uint64_t i) {
    *buf++ = i >> 56;
    *buf++ = i >> 48;
    *buf++ = i >> 40;
    *buf++ = i >> 32;
    *buf++ = i >> 24;
    *buf++ = i >> 16;
    *buf++ = i >> 8;
    *buf++ = i;
}

uint32_t Serialization::unpacki16(unsigned char const *buf) {
    return (buf[0] << 8) | buf[1];
}

uint32_t Serialization::unpacki32(unsigned char const *buf) {
    return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

void  Serialization::packi64(Bytes& bytes, unsigned int i) {
    unsigned char buf[8];
    packi64(buf,i);
    bytes.insert(bytes.end(),buf,buf+sizeof buf);
}

void  Serialization::packi32(Bytes &bytes, unsigned int i) {
    unsigned char buf[4];
    packi32(buf,i);
    bytes.insert(bytes.end(),buf,buf+sizeof buf);
}

void  Serialization::packi16(Bytes& bytes, unsigned int i) {
    unsigned char buf[2];
    packi16(buf,i);
    bytes.insert(bytes.end(),buf,buf+sizeof buf);
}