#ifndef sc_crypt_h
#define sc_crypt_h

#include <stdint.h>
#include <string>

namespace scnet
{

class Crypt
{
public:
    static void encrypt(unsigned char *content, size_t contentLen, const std::string &rc4Key, unsigned char offset, unsigned char mask);
    static void decrypt(unsigned char *content, size_t contentLen, const std::string &rc4Key, unsigned char offset, unsigned char mask);
    static void encrypt(std::string &content, const std::string &rc4Key, unsigned char offset, unsigned char mask);
    static void decrypt(std::string &content, const std::string &rc4Key, unsigned char offset, unsigned char mask);
};

}

#endif
