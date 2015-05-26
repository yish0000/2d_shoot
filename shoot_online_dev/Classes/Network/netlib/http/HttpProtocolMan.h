#ifndef _SC_HttpProtocolMan_h
#define _SC_HttpProtocolMan_h

#include <functional>
#include "HttpMan.h"
#include "../stream/StreamCoder.h"

namespace scnet
{

class Protocol;

class HttpProtocolMan : public HttpHandler
{    
public:

	enum
    {
        PROTOCOL_TIMEOUT = 30,
		PROTOCOL_MAX_LEN = 65536,
    };

	typedef std::function<void(const Protocol*)> ProtoHandler;
        
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

	void setProtoHandler(ProtoHandler ph)
	{
		_protoHandler = ph;
	}

	bool init(int threadNums);
	void stop();

    void get(const std::string &url, int timeout = PROTOCOL_TIMEOUT);
    void post(const std::string &url, const Protocol *p, int timeout = PROTOCOL_TIMEOUT);
    
private:
    void onResponseSuccess(const HttpReq &req, const std::string &res);
    void onResponseFailed(const HttpReq &req);
    void onNewProtocol(const HttpReq &req, const Protocol* p);
    
private:
    const ProtocolCoder *_coder;
    std::string _inEncryptKey;
    std::string _outEncryptKey;
    bool _compress;
	ProtoHandler _protoHandler;

	HttpProtocolMan();
};

}

#endif
