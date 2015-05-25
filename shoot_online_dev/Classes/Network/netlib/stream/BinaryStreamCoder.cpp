#include "BinaryStreamCoder.h"
#include "../protocol/Protocol.h"
#include "cocos2d.h"

namespace scnet
{
	void BinaryStreamCoder::encode(const StreamObj &obj, std::string &content) const
	{
        BinaryStream bs;
        bs << obj;
        
        content = bs.data();
	}

	bool BinaryStreamCoder::decode(const std::string &content, StreamObj &obj) const
	{
		try
		{
			BinaryStream bs(content);
			bs >> obj;
			return true;
		}
		catch (...)
		{
			CCLOG("BinaryStreamCoder decode exception");
			return false;
		}
	}

    void BinaryProtocolCoder::encode(const Protocol *p, std::string &content) const
    {
        BinaryStream bs;
        bs << *p;

        content = bs.data();
    }
    
    Protocol *BinaryProtocolCoder::decode(const std::string &content) const
    {
        Protocol *p = NULL;
    	try
    	{
			BinaryStream bs(content);
			int type;
			bs >> type;
			p = Protocol::create(type);
			if (p != NULL)
			{
				bs.beginRead();
				bs >> *p;
			}
			return p;
    	}
    	catch (...)
    	{
            if (p)
                delete p;
    		CCLOG("BinaryProtocolCoder decode exception");
    		return NULL;
    	}
    }
}
