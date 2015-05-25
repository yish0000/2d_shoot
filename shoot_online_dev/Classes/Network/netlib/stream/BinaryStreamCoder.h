#ifndef _SC_BinaryStreamCoder_
#define _SC_BinaryStreamCoder_

#include "StreamCoder.h"

namespace scnet
{
	class BinaryStreamCoder : public StreamCoder
	{
	private:
		BinaryStreamCoder() {}
	public:
		static BinaryStreamCoder *getDefaultInstance()
		{
			static BinaryStreamCoder inst;
			return &inst;
		}
        virtual void encode(const StreamObj &t, std::string &content) const;
        virtual bool decode(const std::string &content, StreamObj &t) const;
	};

    class BinaryProtocolCoder : public ProtocolCoder
    {
	private:
		BinaryProtocolCoder() {}
    public:
		static BinaryProtocolCoder *getDefaultInstance()
		{
			static BinaryProtocolCoder inst;
			return &inst;
		}
        virtual void encode(const Protocol *p, std::string &content) const;
        virtual Protocol *decode(const std::string &content) const;
    };
};

#endif
