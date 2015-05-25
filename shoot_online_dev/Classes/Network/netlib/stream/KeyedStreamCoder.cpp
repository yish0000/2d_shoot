#include "KeyedStreamCoder.h"
#include "../protocol/Protocol.h"
#include "cocos2d.h"

namespace scnet
{

	void KeyedStreamCoder::encode(const StreamObj &obj, std::string &content) const
	{
        KeyedStream stream;
        stream.pushRootObject(obj);

        content = stream.data();
	}

	bool KeyedStreamCoder::decode(const std::string &content, StreamObj &obj) const
	{
    	try
    	{
			KeyedStream stream(content);
			stream.popRootObject(obj);
			return true;
    	}
    	catch (...)
    	{
    		CCLOG("KeyedStreamCoder decode exception");
    		return false;
    	}
	}

    void KeyedProtocolCoder::encode(const Protocol *p, std::string &content) const
    {
        KeyedStream stream;
        stream.pushRootObject(*p);
        
        content = stream.data();
    }
    
    Protocol *KeyedProtocolCoder::decode(const std::string &content) const
    {
        Protocol *p = NULL;
    	try
    	{
			KeyedStream stream(content);
			int type;
			stream.pop("type", type);
			p = Protocol::create(type);
			if (p != NULL)
			{
				stream.popRootObject(*p);
			}
			return p;
    	}
    	catch (...)
    	{
            if (p)
                delete p;
    		CCLOG("KeyedProtocolCoder decode exception");
    		return NULL;
    	}
    }
};
