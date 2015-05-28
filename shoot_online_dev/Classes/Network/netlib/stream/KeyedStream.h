#ifndef _SC_KeyedStream_h
#define _SC_KeyedStream_h

#include "BinaryStream.h"
#include <vector>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <stdint.h>

namespace scnet
{

class KeyedStream;
class KeyedStreamObj
{
public:
    virtual ~KeyedStreamObj() {}
    
protected:
    virtual void encode(KeyedStream &stream) const = 0;
    virtual void decode(const KeyedStream &stream) = 0;
    
    friend class KeyedStream;
};

class KeyedStream : public BinaryStreamObj
{
    void beginPop()
    {
        BinaryStream bs;
        bs.swap(_bs);
        bs.beginRead();
        bs >> _kv >> _bs;
        _bs.beginRead();
        
        std::map<std::string, KeyedStream>::iterator it = _kv.begin(), ie = _kv.end();
        for (; it != ie; ++it)
            it->second.beginPop();
    }
    
    void finishPush()
    {
        std::map<std::string, KeyedStream>::iterator it = _kv.begin(), ie = _kv.end();
        for (; it != ie; ++it)
            it->second.finishPush();
        
        BinaryStream bs;
        bs << _kv << _bs;
        bs.swap(_bs);
    }
    
    template <typename T>
    KeyedStream &pushPrimaryType(const std::string &key, const T &val)
    {
        _kv[key]._bs << val;
        return *this;
    }
    
    template <typename T>
    const KeyedStream &popPrimaryType(const std::string &key, T &val) const
    {
        std::map<std::string, KeyedStream>::const_iterator it = _kv.find(key);
        if (it != _kv.end())
        {
            const KeyedStream &s = it->second;
            s._bs.beginRead();
            s._bs >> val;
        }
        return *this;
    }
    
public:
    explicit KeyedStream(const std::string &data=std::string()):_bs(data)
    {
        if (!data.empty())
            beginPop();
    }
    
    void pushRootObject(const KeyedStreamObj &rootObj)
    {
        rootObj.encode(*this);
        finishPush();
    }
    
    void popRootObject(KeyedStreamObj &rootObj)
    {
        rootObj.decode(*this);
    }
    
    const std::string &data() const
    {
        return _bs.data();
    }
    
    virtual void encode(BinaryStream &stream) const
    {
        stream << _bs;
    }
    
    virtual void decode(const BinaryStream &stream)
    {
        stream >> _bs;
    }

	KeyedStream &push(const std::string &key, bool val)
	{
		return pushPrimaryType(key, val);
	}

	const KeyedStream &pop(const std::string &key, bool &val) const
	{
		return popPrimaryType(key, val);
	}
    
    KeyedStream &push(const std::string &key, int8_t val)
    {
        return pushPrimaryType(key, val);
    }
    
    const KeyedStream & pop(const std::string &key, int8_t &val) const
    {
        return popPrimaryType(key, val);
    }
    
    KeyedStream & push(const std::string &key, uint8_t val)
    {
        return pushPrimaryType(key, val);
    }
    
    const KeyedStream & pop(const std::string &key, uint8_t &val) const
    {
        return popPrimaryType(key, val);
    }
    
    KeyedStream & push(const std::string &key, int16_t val)
    {
        return pushPrimaryType(key, val);
    }
    
    const KeyedStream & pop(const std::string &key, int16_t &val) const
    {
        return popPrimaryType(key, val);
    }
    
    KeyedStream & push(const std::string &key, uint16_t val)
    {
        return pushPrimaryType(key, val);
    }
    
    const KeyedStream & pop(const std::string &key, uint16_t &val) const
    {
        return popPrimaryType(key, val);
    }
    
    KeyedStream & push(const std::string &key, int32_t val)
    {
        return pushPrimaryType(key, val);
    }
    
    const KeyedStream & pop(const std::string &key, int32_t &val) const
    {
        return popPrimaryType(key, val);
    }
    
    KeyedStream & push(const std::string &key, uint32_t val)
    {
        return pushPrimaryType(key, val);
    }
    
    const KeyedStream & pop(const std::string &key, uint32_t &val) const
    {
        return popPrimaryType(key, val);
    }
    
    KeyedStream & push(const std::string &key, int64_t val)
    {
        return pushPrimaryType(key, val);
    }
    
    const KeyedStream & pop(const std::string &key, int64_t &val) const
    {
        return popPrimaryType(key, val);
    }
    
    KeyedStream & push(const std::string &key, uint64_t val)
    {
        return pushPrimaryType(key, val);
    }
    
    const KeyedStream & pop(const std::string &key, uint64_t &val) const
    {
        return popPrimaryType(key, val);
    }
    
    KeyedStream & push(const std::string &key, float val)
    {
        return pushPrimaryType(key, val);
    }

    const KeyedStream & pop(const std::string &key, float &val) const
    {
        return popPrimaryType(key, val);
    }

    KeyedStream & push(const std::string &key, double val)
    {
        return pushPrimaryType(key, val);
    }

    const KeyedStream & pop(const std::string &key, double &val) const
    {
        return popPrimaryType(key, val);
    }

    KeyedStream & push(const std::string &key, const std::string &val)
    {
        return pushPrimaryType(key, val);
    }
    
    const KeyedStream & pop(const std::string &key, std::string &val) const
    {
        return popPrimaryType(key, val);
    }
    
    KeyedStream & push(const std::string &key, const char *val)
    {
        return pushPrimaryType(key, val);
    }
    
    KeyedStream & push(const std::string &key, const KeyedStreamObj &obj)
    {
        obj.encode(_kv[key]);
        return *this;
    }
    
    const KeyedStream &pop(const std::string &key, KeyedStreamObj &obj) const
    {
        std::map<std::string, KeyedStream>::const_iterator it = _kv.find(key);
        if (it != _kv.end())
        {
            const KeyedStream &s = it->second;
            obj.decode(s);
        }
        return *this;
    }
    
    template <typename T>
    KeyedStream &push(const std::vector<T> &val)
    {
        uint32_t count = (uint32_t)val.size();
        for (uint32_t i = 0; i < count; ++i)
        {
            std::stringstream ss;
            ss << i;
            push(ss.str(), val[i]);
        }
        
        return *this;
    }
    
    template <typename T>
    KeyedStream &push(const std::set<T> &val)
    {
        typename std::set<T>::const_iterator it = val.begin(), ie = val.end();
        for (int i = 0; it != ie; ++i, ++it)
        {
            std::stringstream ss;
            ss << i;
            push(ss.str(), *it);
        }
        
        return *this;
    }
    
    template <typename T>
    KeyedStream &push(const std::string &key, const std::vector<T> &val)
    {
        _kv[key].push(val);
        return *this;
    }
    
    template <typename T>
    KeyedStream &push(const std::string &key, const std::set<T> &val)
    {
        _kv[key].push(val);
        return *this;
    }
    
    template <typename T>
    const KeyedStream &pop(std::vector<T> &val) const
    {
        val.reserve(_kv.size());
        std::map<std::string, KeyedStream>::const_iterator it = _kv.begin(), ie = _kv.end();
        for (; it != ie; ++it)
        {
            val.push_back(T());
            pop(it->first, val.back());
        }
        return *this;
    }
    
    template <typename T>
    const KeyedStream &pop(const std::string &key, std::vector<T> &val) const
    {
        std::map<std::string, KeyedStream>::const_iterator it = _kv.find(key);
        if (it != _kv.end())
            it->second.pop(val);
        return *this;
    }
    
    template <typename T>
    const KeyedStream &pop(std::set<T> &val) const
    {
        std::map<std::string, KeyedStream>::const_iterator it = _kv.begin(), ie = _kv.end();
        for (; it != ie; ++it)
        {
            T t;
            pop(it->first, t);
            val.insert(t);
        }
        return *this;
    }
    
    template <typename T>
    const KeyedStream &pop(const std::string &key, std::set<T> &val) const
    {
        std::map<std::string, KeyedStream>::const_iterator it = _kv.find(key);
        if (it != _kv.end())
            it->second.pop(val);
        return *this;
    }
    
    //K is integer type or std::string type, support 64-bit
    template <typename K, typename V>
    KeyedStream &push(const std::string &key, const std::map<K, V> &val)
    {
        KeyedStream &ks = _kv[key];
        typename std::map<K, V>::const_iterator it = val.begin(), ie = val.end();
        for (; it != ie; ++it)
        {
            std::stringstream ss;
            ss << it->first;
            ks.push(ss.str(), it->second);
        }
        return *this;
    }
    
    //K is integer type or std::string type, support 64-bit
    template <typename K, typename V>
    const KeyedStream &pop(const std::string &key, std::map<K, V> &val) const
    {
        std::map<std::string, KeyedStream>::const_iterator kvit = _kv.find(key);
        if (kvit == _kv.end())
            return *this;
        
        const KeyedStream &ks = kvit->second;
        std::map<std::string, KeyedStream>::const_iterator it = ks._kv.begin(), ie = ks._kv.end();
        for (; it != ie; ++it)
        {
            std::stringstream ss(it->first);
            K k;
            ss >> k;
            ks.pop(it->first, val[k]);
        }
        return *this;
    }
    
    void swap(KeyedStream &rhs)
    {
        _kv.swap(rhs._kv);
        _bs.swap(rhs._bs);
    }
    
private:
    std::map<std::string, KeyedStream> _kv;
    BinaryStream _bs;
};

}

#endif
