#ifndef _SC_JsonStreamCoder_h
#define _SC_JsonStreamCoder_h

#include "StreamCoder.h"

namespace scnet
{
	class JsonStreamCoder : public StreamCoder
	{
	private:
		JsonStreamCoder() {}
	public:
		static JsonStreamCoder *getDefaultInstance()
		{
			static JsonStreamCoder inst;
			return &inst;
		}

		virtual void encode(const StreamObj &t, std::string &content) const;
		virtual bool decode(const std::string &content, StreamObj &t) const;
	};

    class JsonProtocolCoder : public ProtocolCoder
    {
	private:
		JsonProtocolCoder() {}
    public:
		static JsonProtocolCoder *getDefaultInstance()
		{
			static JsonProtocolCoder inst;
			return &inst;
		}

        virtual void encode(const Protocol *p, std::string &content) const;
        virtual Protocol *decode(const std::string &content) const;
    };
};

#endif
