#include "crypt.h"
#include "rc4.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

namespace scnet
{
    void Crypt::encrypt(unsigned char *content, size_t contentLen, const std::string &rc4Key, unsigned char offset, unsigned char mask)
    {
        RC4 rc4((const uint8_t *)rc4Key.c_str(), rc4Key.length());
        rc4.crypt(content, content, contentLen);
        
        for (size_t i = 0; i < contentLen; ++i)
        {
            content[i] = (content[i]^mask)-offset;
        }
        
        for (size_t i = 0; i < contentLen/2; ++i)
        {
            size_t swapIndex = contentLen-i-1;
            content[i] ^= content[swapIndex];
            content[swapIndex] ^= content[i];
            content[i] ^= content[swapIndex];
        }
    }
    
    void Crypt::decrypt(unsigned char *content, size_t contentLen, const std::string &rc4Key, unsigned char offset, unsigned char mask)
    {
        for (size_t i = 0; i < contentLen/2; ++i)
        {
            size_t swapIndex = contentLen-i-1;
            content[i] ^= content[swapIndex];
            content[swapIndex] ^= content[i];
            content[i] ^= content[swapIndex];
        }
        
        for (size_t i = 0; i < contentLen; ++i)
        {
            content[i] = (content[i]+offset)^mask;
        }
        
        RC4 rc4((const uint8_t *)rc4Key.c_str(), rc4Key.length());
        rc4.crypt(content, content, contentLen);
    }
    
    void Crypt::encrypt(std::string &content, const std::string &rc4Key, unsigned char offset, unsigned char mask)
    {
        RC4 rc4((const uint8_t *)rc4Key.c_str(), rc4Key.length());
        rc4.crypt(content, content);
        
        size_t len = content.size();
        for (size_t i = 0; i < len; ++i)
        {
            content[i] = (content[i]^mask)-offset;
        }
        
        for (size_t i = 0; i < len/2; ++i)
        {
            size_t swapIndex = len-i-1;
            content[i] ^= content[swapIndex];
            content[swapIndex] ^= content[i];
            content[i] ^= content[swapIndex];
        }
    }

    void Crypt::decrypt(std::string &content, const std::string &rc4Key, unsigned char offset, unsigned char mask)
    {
        size_t len = content.size();
        for (size_t i = 0; i < len/2; ++i)
        {
            size_t swapIndex = len-i-1;
            content[i] ^= content[swapIndex];
            content[swapIndex] ^= content[i];
            content[i] ^= content[swapIndex];
        }
        
        for (size_t i = 0; i < len; ++i)
        {
            content[i] = (content[i]+offset)^mask;
        }
        
        RC4 rc4((const uint8_t *)rc4Key.c_str(), rc4Key.length());
        rc4.crypt(content, content);
    }
}
