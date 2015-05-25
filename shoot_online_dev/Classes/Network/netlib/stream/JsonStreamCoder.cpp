#include "JsonStreamCoder.h"
#include "../protocol/Protocol.h"
#include "cocos2d.h"

namespace scnet
{
	void JsonStreamCoder::encode(const StreamObj &obj, std::string &content) const
	{
		Json::Value root;
		JsonStream stream(root);
		stream.pushRootObject(obj);

		content = root.toStyledString();
	}

	bool JsonStreamCoder::decode(const std::string &content, StreamObj &obj) const
	{
    	try
    	{
			Json::Reader reader;
			Json::Value root;
			if (!reader.parse(content, root))
				return false;

			JsonStream stream(root);
			stream.popRootObject(obj);
			return true;
    	}
    	catch (...)
    	{
    		CCLOG("JsonStreamCoder decode exception");
    		return false;
    	}
	}

    void JsonProtocolCoder::encode(const Protocol *p, std::string &content) const
    {
        Json::Value root;
        JsonStream stream(root);
        stream.pushRootObject(*p);
        
        content = root.toStyledString();
    }

    Protocol *JsonProtocolCoder::decode(const std::string &content) const
    {
        Protocol *p = NULL;
    	try
    	{
			Json::Reader reader;
			Json::Value root;
			if (!reader.parse(content, root))
				return NULL;
			int type = root["type"].asInt();
			p = Protocol::create(type);
			if (p != NULL)
			{
				JsonStream stream(root);
				stream.popRootObject(*p);
			}
			return p;
    	}
    	catch (...)
    	{
            if (p)
                delete p;
    		CCLOG("JsonProtocolCoder decode exception");
    		return NULL;
    	}
    }
}
