//
//  ZlibUtil.h
//  BaccaratMania
//
//  Created by 吴碧海 on 13-6-12.
//
//

#ifndef __BaccaratMania__ZLibUtil__
#define __BaccaratMania__ZLibUtil__

#include <string>

namespace wge
{
class ZLibUtil
{
public:
    static bool inflate(const std::string &ibuffer, std::string &obuffer);
    static bool deflate(const std::string &ibuffer, std::string &obuffer);
};
}

#endif /* defined(__BaccaratMania__ZlibUtil__) */
