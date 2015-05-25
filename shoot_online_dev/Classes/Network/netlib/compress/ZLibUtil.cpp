//
//  ZlibUtil.cpp
//  BaccaratMania
//
//  Created by 吴碧海 on 13-6-12.
//
//

#include "ZLibUtil.h"
#include "WAssert.h"
#include <zlib.h>
#include <string.h>

namespace wge
{
    bool ZLibUtil::inflate(const std::string &ibuffer, std::string &obuffer)
    {
        size_t bufferSize = ibuffer.size();        
        char out[bufferSize];
        
        z_stream d_stream; /* decompression stream */
        d_stream.zalloc = (alloc_func)0;
        d_stream.zfree = (free_func)0;
        d_stream.opaque = (voidpf)0;
        
        d_stream.next_in  = (Bytef *)ibuffer.data();
        d_stream.avail_in = bufferSize;
        d_stream.next_out = (Bytef *)out;
        d_stream.avail_out = bufferSize;
        
        int err = Z_OK;
        if( (err = ::inflateInit2(&d_stream, -MAX_WBITS)) != Z_OK )
            return false;
        
        std::string tempOBuffer;
        size_t reserveSize = bufferSize*5;
        if (reserveSize > 256*1024)
            tempOBuffer.reserve(bufferSize*2);
        else
            tempOBuffer.reserve(reserveSize);
        
        while (true)
        {
            err = ::inflate(&d_stream, Z_NO_FLUSH);
            
            if (err == Z_STREAM_END)
                break;
            
            switch (err)
            {
                case Z_OK:
                    WGEASSERT(d_stream.avail_out == 0);
                    tempOBuffer.insert(tempOBuffer.end(), out, out+bufferSize);
                    d_stream.next_out = (Bytef *)out;
                    d_stream.avail_out = bufferSize;
                    break;
                default:
                    ::inflateEnd(&d_stream);
                    return false;
            }
        }
        
        tempOBuffer.insert(tempOBuffer.end(), out, out+bufferSize-d_stream.avail_out);
        
        err = ::inflateEnd(&d_stream);
        if (err != Z_OK)
            return false;
        else
            obuffer.swap(tempOBuffer);
        return true;
    }
    
    bool ZLibUtil::deflate(const std::string &ibuffer, std::string &obuffer)
    {
        size_t bufferSize = ibuffer.size();        
        char out[bufferSize];
        
        z_stream d_stream; /* decompression stream */
        d_stream.zalloc = (alloc_func)0;
        d_stream.zfree = (free_func)0;
        d_stream.opaque = (voidpf)0;
        
        d_stream.next_in  = (Bytef *)ibuffer.data();
        d_stream.avail_in = bufferSize;
        d_stream.next_out = (Bytef *)out;
        d_stream.avail_out = bufferSize;
        
        int err = Z_OK;
        if( (err = deflateInit2(&d_stream, 9, Z_DEFLATED, -MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY)) != Z_OK )
            return false;
        
        std::string tempOBuffer;
        size_t reserveSize = bufferSize*2;
        if (reserveSize > 256*1024)
            tempOBuffer.reserve(bufferSize*1.5);
        else
            tempOBuffer.reserve(reserveSize);

        do
        {
            err = ::deflate(&d_stream, Z_NO_FLUSH);
            
            WGEASSERT(err != Z_STREAM_END);
            
            switch (err)
            {
                case Z_OK:
                    if (d_stream.avail_out == 0)
                    {
                        tempOBuffer.insert(tempOBuffer.end(), out, out+bufferSize);
                        d_stream.next_out = (Bytef *)out;
                        d_stream.avail_out = bufferSize;
                    }
                    break;
                default:
                    ::inflateEnd(&d_stream);
                    return false;
            }
        }
        while (d_stream.avail_in > 0);
        
        while (true)
        {
            err = ::deflate(&d_stream, Z_FINISH);
            
            if (err == Z_STREAM_END)
                break;
            
            switch (err)
            {
                case Z_OK:
                    if (d_stream.avail_out == 0)
                    {
                        tempOBuffer.insert(tempOBuffer.end(), out, out+bufferSize);
                        d_stream.next_out = (Bytef *)out;
                        d_stream.avail_out = bufferSize;
                    }
                    break;
                default:
                    ::inflateEnd(&d_stream);
                    return false;
            }
        }
        
        tempOBuffer.insert(tempOBuffer.end(), out, out+bufferSize-d_stream.avail_out);
        
        err = ::deflateEnd(&d_stream);
        if (err != Z_OK)
            return false;
        else
            obuffer.swap(tempOBuffer);
        return true;
    }
}
