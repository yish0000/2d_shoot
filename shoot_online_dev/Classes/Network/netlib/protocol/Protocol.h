#ifndef _SC_Protocol_h
#define _SC_Protocol_h

#include "../Stream/StreamCoder.h"

namespace scnet
{

class Protocol : public StreamObj
{
public:
    Protocol():type(0)
    {}
    
    Protocol(int t):type(t)
    {}
    
    virtual ~Protocol() {}
        
    static Protocol *create(int type);
    
protected:
	virtual void encode(JsonStream &stream) const;
	virtual void decode(const JsonStream &stream);

	virtual void encode(BinaryStream &stream) const;
	virtual void decode(const BinaryStream &stream);

	virtual void encode(KeyedStream &stream) const;
	virtual void decode(const KeyedStream &stream);

public:
    int type;
};

typedef Protocol *(*CreateFunc)();

class ProtocolRegister
{
public:
    ProtocolRegister(int, CreateFunc);
};

#define DECLARE_CREATE_FUNC(CLASS) \
static Protocol *create() \
{\
	return new CLASS(); \
}

#define REGISTER_PROTOCOL(TYPE, CLASS) \
	scnet::ProtocolRegister g_ProtocolRegister_##CLASS(TYPE, &CLASS::create)
    
#define DECLARE_REGISTER_PROTOCOL(CLASS) \
	extern scnet::ProtocolRegister g_ProtocolRegister_##CLASS;\
	void* tmp_##CLASS = &g_ProtocolRegister_##CLASS

}

#endif
