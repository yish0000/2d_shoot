#ifndef _SC_StreamCoder_h
#define _SC_StreamCoder_h

#include <string>
#include "JsonStream.h"
#include "BinaryStream.h"
#include "KeyedStream.h"

namespace scnet
{
	class StreamObj : public JsonStreamObj, public BinaryStreamObj, public KeyedStreamObj
	{
	public:
		StreamObj() {}
		virtual ~StreamObj() {}

	protected:
		virtual void encode(JsonStream &stream) const
		{}
		virtual void decode(const JsonStream &stream)
		{}

		virtual void encode(BinaryStream &stream) const
		{}
		virtual void decode(const BinaryStream &stream)
		{}

		virtual void encode(KeyedStream &stream) const
		{}
		virtual void decode(const KeyedStream &stream)
		{}
	};

    class StreamCoder
    {
    public:
    	virtual ~StreamCoder() {}

        virtual void encode(const StreamObj &t, std::string &content) const = 0;
        virtual bool decode(const std::string &content, StreamObj &t) const = 0;
    };
    
    class Protocol;
    class ProtocolCoder
    {
    public:
    	virtual ~ProtocolCoder() {}

        virtual void encode(const Protocol *p, std::string &content) const = 0;
        virtual Protocol *decode(const std::string &content) const = 0;
    };
};

#endif
