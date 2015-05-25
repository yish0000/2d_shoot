#include "Protocol.h"
#include <map>

namespace scnet
{

static std::map<int, CreateFunc> &getMap()
{
    static std::map<int, CreateFunc> map;
    return map;
}

ProtocolRegister::ProtocolRegister(int type, CreateFunc create)
{
    getMap()[type] = create;
}

Protocol *Protocol::create(int type)
{
    std::map<int, CreateFunc>::const_iterator it = getMap().find(type);
    if (it == getMap().end())
        return NULL;
    return (*it->second)();
}

void Protocol::encode(JsonStream &stream) const
{
    stream.push("type", type);
}

void Protocol::decode(const JsonStream &stream)
{
    stream.pop("type", type);
}
    
void Protocol::encode(BinaryStream &stream) const
{
    stream << type;
}

void Protocol::decode(const BinaryStream &stream)
{
    stream >> type;
}
    
void Protocol::encode(KeyedStream &stream) const
{
    stream.push("type", type);
}

void Protocol::decode(const KeyedStream &stream)
{
    stream.pop("type", type);
}

}
