#ifndef _SC_HttpCurl_h
#define _SC_HttpCurl_h

#include <string>

namespace scnet
{

class HttpCurl
{
private:
    HttpCurl()
    {}
    
public:
    static bool get(const std::string &url, std::string &res, int timeout);
    static bool post(const std::string &url, const std::string &req, std::string &res, int timeout);
};

};

#endif
