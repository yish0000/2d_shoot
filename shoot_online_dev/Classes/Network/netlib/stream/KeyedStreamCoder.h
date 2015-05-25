#ifndef _SC_KeyedStreamCoder_h_
#define _SC_KeyedStreamCoder_h_

#include "StreamCoder.h"

namespace scnet
{

	class KeyedStreamCoder : public StreamCoder
	{
	private:
		KeyedStreamCoder() {}
	public:
		static KeyedStreamCoder *getDefaultInstance()
		{
			static KeyedStreamCoder inst;
			return &inst;
		}
		virtual void encode(const StreamObj &t, std::string &content) const;
		virtual bool decode(const std::string &content, StreamObj &t) const;
	};

    class KeyedProtocolCoder : public ProtocolCoder
    {
	private:
		KeyedProtocolCoder() {}
    public:
		static KeyedProtocolCoder *getDefaultInstance()
		{
			static KeyedProtocolCoder inst;
			return &inst;
		}
        virtual void encode(const Protocol *p, std::string &content) const;
        virtual Protocol *decode(const std::string &content) const;
    };

};

#endif
