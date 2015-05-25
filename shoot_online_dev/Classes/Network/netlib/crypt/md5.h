//
//  md5.h
//
//  Created by �寸�娴�on 12-7-28.
//  Copyright (c) 2012骞�GameDream. All rights reserved.
//

#ifndef wge_md5_h
#define wge_md5_h

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 rights reserved.
 
 License to copy and use this software is granted provided that it
 is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 Algorithm" in all material mentioning or referencing this software
 or this function.
 
 License is also granted to make and use derivative works provided
 that such works are identified as "derived from the RSA Data
 Security, Inc. MD5 Message-Digest Algorithm" in all material
 mentioning or referencing the derived work.
 
 RSA Data Security, Inc. makes no representations concerning either
 the merchantability of this software or the suitability of this
 software for any particular purpose. It is provided "as is"
 without express or implied warranty of any kind.
 
 These notices must be retained in any copies of any part of this
 documentation and/or software.
 */

#include <string>
#include <stdint.h>

namespace wge
{
class MD5
{
private:
    typedef unsigned char *POINTER;
    
    /* UINT4 defines a four byte word */
    typedef uint32_t UINT4;
    
    /* MD5 context. */
    typedef struct {
        UINT4 state[4];                                   /* state (ABCD) */
        UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
        unsigned char buffer[64];                         /* input buffer */
    } MD5_CTX;
    
    MD5_CTX _ctx;
    
public:
    MD5();
    
    void update(const unsigned char *content, unsigned int len);
    void update(const std::string &content);
    void final(unsigned char (&md5)[16]);
    void final(char (&md5)[32]);
    void final(std::string &md5, bool hexAscii=false);
    
private:
    void init();
    static void transform(UINT4 state[4], const unsigned char block[64]);
};
};

#endif
