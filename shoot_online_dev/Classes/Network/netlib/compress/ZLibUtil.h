#ifndef _SC_ZLibUtil_
#define _SC_ZLibUtil_

#include <string>

namespace scnet
{

class ZLibUtil
{
public:
    static bool inflate(const std::string &ibuffer, std::string &obuffer);
    static bool deflate(const std::string &ibuffer, std::string &obuffer);
};

}

#endif
