#include "HttpProtocolMan.h"
#include "../protocol/Protocol.h"
#include "../protocol/Processor.h"
#include "../crypt/rc4.h"
#include "../compress/ZLibUtil.h"
#include "cocos2d.h"

namespace scnet
{

HttpProtocolMan::HttpProtocolMan() : _coder(NULL), _compress(false), _protoHandler(nullptr)
{
}

HttpProtocolMan::~HttpProtocolMan()
{
}

bool HttpProtocolMan::init(int threadNums)
{
	return HttpMan::getInstance()->init(threadNums);
}

void HttpProtocolMan::stop()
{
	HttpMan::getInstance()->stop();
}

void HttpProtocolMan::get(const std::string &url, int timeout /* = PROTOCOL_TIMEOUT */)
{
	HttpMan::getInstance()->get(url, this, timeout, 0);
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
            CCLOG("HttpProtocolMan::post, compress failed, length=%zu", content.size());
            return;
        }
        else
            CCLOG("HttpProtocolMan::post, compress success, rawLength=%zu, deflateLength=%zu", content.size(), compressedBytes.size());
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
        CCLOG("HttpProtocolMan::post, protocol length invalid, length=%zu", content.size());
        return;
    }
    
    HttpMan::getInstance()->post(url, content, this, timeout, 0);
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
        CCLOG("HttpProtocolMan, received invalid protocol");
        onNewProtocol(req, NULL);
    }
    else
    {
		onNewProtocol(req, p);
    }
}

void HttpProtocolMan::onResponseFailed(const HttpReq &req)
{
    CCLOG("HttpProtocolMan, onResponseFailed");
	onNewProtocol(req, NULL);
}

void HttpProtocolMan::onNewProtocol(const HttpReq &req, const Protocol* p)
{
    if (p)
    {
        const Processor *proc = Processor::getProcessor(p->type);
        if (proc)
        {
            proc->process(p);
            return;
        }

		if( _protoHandler )
			_protoHandler(p);
    }
	else
	{
		CCLOG("Invalid protocol!! url=%s, body=%s", req.url.c_str(), req.body.c_str());
	}
}

}
