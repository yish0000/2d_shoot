//
//  crypt.h
//
//  Created by 吴碧海 on 13-4-29.
//
//

#ifndef wge_crypt_h
#define wge_crypt_h

#include <stdint.h>
#include <string>

namespace wge
{
class Crypt
{
public:
    static void encrypt(unsigned char *content, size_t contentLen, const std::string &rc4Key, unsigned char offset, unsigned char mask);
    static void decrypt(unsigned char *content, size_t contentLen, const std::string &rc4Key, unsigned char offset, unsigned char mask);
    static void encrypt(std::string &content, const std::string &rc4Key, unsigned char offset, unsigned char mask);
    static void decrypt(std::string &content, const std::string &rc4Key, unsigned char offset, unsigned char mask);
};
};

#endif
