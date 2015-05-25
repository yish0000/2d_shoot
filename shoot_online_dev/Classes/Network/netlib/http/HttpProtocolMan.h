//
//  HttpProtocolMan.h
//
//  Created by bihai wu on 12-3-22.
//

#ifndef _HttpProtocolMan_h
#define _HttpProtocolMan_h

#include "WEvent.h"
#include "HttpMan.h"
#include "StreamCoder.h"

namespace wge
{
#define kEventTypeHttpProtocolError "kEventTypeHttpProtocolError"

class HttpProtocolErrorEvent : public WEvent
{
public:
    HttpProtocolErrorEvent(const std::string &type, const std::string &url_, const std::string &body_)
    :WEvent(type),url(url_),body(body_)
    {}
    
public:
    std::string url;
    std::string body;
};

class HttpProtocolMan : public HttpHandler, public WEventDispatcher, public WEventListener
{    
private:
    enum
    {
        kProtocolTimeout = 30,
    };
    
    HttpProtocolMan();
    
public:
    virtual ~HttpProtocolMan();
    
    static HttpProtocolMan *getInstance()
    {
        static HttpProtocolMan instance;
        return &instance;
    }
    
    void setProtocolCoder(const ProtocolCoder *coder)
    {
        _coder = coder;
    }
    void setEncryptKey(const std::string &inEncryptKey, const std::string &outEncryptKey)
    {
        _inEncryptKey = inEncryptKey;
        _outEncryptKey = outEncryptKey;
    }
    void setCompress(bool compress)
    {
        _compress = compress;
    }
    void get(const std::string &url, int timeout = kProtocolTimeout)
    {
        HttpMan::getInstance()->get(url, this, timeout, HttpMan::PRIORITY_PROTOCOL);
    }
    void post(const std::string &url, const Protocol *p, int timeout = kProtocolTimeout);
    
private:
    void onResponseSuccess(const HttpReq &req, const std::string &res);
    void onResponseFailed(const HttpReq &req);
    void onNewProtocol(WEvent *e);
    
private:
    const ProtocolCoder *_coder;
    std::string _inEncryptKey;
    std::string _outEncryptKey;
    bool _compress;
};
};

#endif
