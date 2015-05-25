//
//  HttpProtocolMan.cpp
//
//  Created by bihai wu on 12-3-22.
//

#include "HttpProtocolMan.h"
#include "Protocol.h"
#include "Processor.h"
#include "rc4.h"
#include "WLog.h"
#include "ZLibUtil.h"
#include "NetConfig.h"

namespace wge
{
#define kEventTypeHttpNewProtocol "kEventTypeHttpNewProtocol"

class HttpProtocolEvent : public WEvent
{
public:
    HttpProtocolEvent(const std::string &type):WEvent(type),req(NULL),resp(NULL)
    {}
    
public:
    const struct HttpReq *req;
    Protocol *resp;
};

HttpProtocolMan::HttpProtocolMan():_coder(NULL),_compress(false)
{
    addEventListener(kEventTypeHttpNewProtocol, this, weventcallback_selector(HttpProtocolMan::onNewProtocol));
}

HttpProtocolMan::~HttpProtocolMan()
{
    removeAllForListener(this);
}

void HttpProtocolMan::post(const std::string &url, const Protocol *p, int timeout)
{
    std::string content;
    _coder->encode(p, content);
    
    if (_compress)
    {
        std::string compressedBytes;
        if (!ZLibUtil::deflate(content, compressedBytes))
        {
            WGE_ERROR("HttpProtocolMan::post, compress failed, length=%zu", content.size());
            return;
        }
        else
            WGE_DEBUG("HttpProtocolMan::post, compress success, rawLength=%zu, deflateLength=%zu", content.size(), compressedBytes.size());
        content.swap(compressedBytes);
    }
    
    if (!_outEncryptKey.empty())
    {
        std::string cipher;
        cipher.reserve(content.size());
        RC4 rc4(_outEncryptKey);
        rc4.crypt(content, cipher);
        content.swap(cipher);
    }
    
    if (content.size() > PROTOCOL_MAX_LEN)
    {
        WGE_ERROR("HttpProtocolMan::post, protocol length invalid, length=%zu", content.size());
        return;
    }
    
    HttpMan::getInstance()->post(url, content, this, timeout, HttpMan::PRIORITY_PROTOCOL);
}

void HttpProtocolMan::onResponseSuccess(const HttpReq &req, const std::string &res)
{
    Protocol *p = NULL;
    if (_inEncryptKey.empty() && !_compress)
        p = _coder->decode(res);
    else
    {
        std::string plain;
        if (!_inEncryptKey.empty())
        {
            RC4 rc4(_inEncryptKey);
            rc4.crypt(res, plain);
        }
        
        if (_compress)
        {
            std::string decompressedBytes;
            if (_inEncryptKey.empty())
                ZLibUtil::inflate(res, decompressedBytes);
            else
                ZLibUtil::inflate(plain, decompressedBytes);
            plain.swap(decompressedBytes);
        }
        p = _coder->decode(plain);
    }
    
    if (!p)
    {
        WGE_ERROR("HttpProtocolMan, received invalid protocol");
        
        HttpProtocolEvent e(kEventTypeHttpNewProtocol);
        e.req = &req;
        dispatchEvent(&e);
    }
    else
    {
        HttpProtocolEvent e(kEventTypeHttpNewProtocol);
        e.req = &req;
        e.resp = p;
        dispatchEvent(&e);
        
        delete p;
    }
}

void HttpProtocolMan::onResponseFailed(const HttpReq &req)
{
    WGE_ERROR("HttpProtocolMan, onResponseFailed");

    HttpProtocolEvent e(kEventTypeHttpNewProtocol);
    e.req = &req;
    dispatchEvent(&e);
}

void HttpProtocolMan::onNewProtocol(WEvent *e)
{
    HttpProtocolEvent *event = dynamic_cast<HttpProtocolEvent *>(e);
    if (event->resp)
    {
        Protocol *resp = event->resp;
        const Processor *proc = Processor::getProcessor(resp->type);
        if (proc)
        {
            proc->process(resp);
            return;
        }
        else
            WGE_ERROR("Fail to find processor for protocol %d", resp->type);
    }
    
    HttpProtocolErrorEvent eventError(kEventTypeHttpProtocolError, event->req->url, event->req->body);
    dispatchEvent(&eventError);
}
};
