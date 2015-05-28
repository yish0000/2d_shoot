#ifndef _SC_JsonStream_h
#define _SC_JsonStream_h

#include <string>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include <stdint.h>
#include <stdlib.h>
#include "../libjson/json/json.h"

namespace scnet
{

class JsonStream;
class JsonStreamObj
{
public:
    virtual ~JsonStreamObj() {}

protected:
    virtual void encode(JsonStream &stream) const = 0;
    virtual void decode(const JsonStream &stream) = 0;
    
    friend class JsonStream;
};

class JsonStream
{
public:
    JsonStream(const Json::Value &value):_value(const_cast<Json::Value &>(value))
    {}
    
    void pushRootObject(const JsonStreamObj &rootObj)
    {
        rootObj.encode(*this);
    }
    
    void popRootObject(JsonStreamObj &rootObj)
    {
        rootObj.decode(*this);
    }

	template <typename K>
	JsonStream &push(const K &key, bool val)
	{
		_value[key] = val;
		return *this;
	}
    
    template <typename K>
    JsonStream &push(const K &key, int8_t val)
    {
        _value[key] = val;
        return *this;
    }

    template <typename K>
    JsonStream &push(const K &key, uint8_t val)
    {
        _value[key] = val;
        return *this;
    }

    template <typename K>
    JsonStream &push(const K &key, int16_t val)
    {
        _value[key] = val;
        return *this;
    }

    template <typename K>
    JsonStream &push(const K &key, uint16_t val)
    {
        _value[key] = val;
        return *this;
    }
    
    template <typename K>
    JsonStream &push(const K &key, int32_t val)
    {
        _value[key] = val;
        return *this;
    }
    
    template <typename K>
    JsonStream &push(const K &key, uint32_t val)
    {
        _value[key] = val;
        return *this;
    }
    
    template <typename K>
    JsonStream &push(const K &key, int64_t val)
    {
        _value[key] = (Json::Value::Int64)val;
        return *this;
    }
    
    template <typename K>
    JsonStream &push(const K &key, uint64_t val)
    {
        _value[key] = (Json::Value::UInt64)val;
        return *this;
    }
    
    template <typename K>
    JsonStream &push(const K &key, float val)
    {
        _value[key] = val;
        return *this;
    }

    template <typename K>
    JsonStream &push(const K &key, double val)
    {
        _value[key] = val;
        return *this;
    }

    template <typename K>
    JsonStream &push(const K &key, const std::string &val)
    {
        _value[key] = val;
        return *this;
    }
    
    template <typename K, typename T1, typename T2>
    JsonStream &push(const K &key, const std::pair<T1, T2> &pair)
    {
        JsonStream stream(_value[key]);
        stream.push(0, pair.first);
        stream.push(1, pair.second);
        return *this;
    }
    
    template <typename K>
    JsonStream &push(const K &key, const JsonStreamObj &val)
    {
        JsonStream stream(_value[key]);
        val.encode(stream);
        return *this;
    }
    
    template <typename K>
    JsonStream &push(const K &key, const Json::Value &value)
    {
        _value[key] = value;
        return *this;
    }
    
    template <typename T>
    JsonStream &push(const std::vector<T> &val)
    {
        uint32_t count = (uint32_t)val.size();
        for (uint32_t i = 0; i < count; ++i)
        {
            push(i, val[i]);
        }
        
        return *this;        
    }
    
    template <typename T>
    JsonStream &push(const std::set<T> &val)
    {
        typename std::set<T>::const_iterator it = val.begin(), ie = val.end();
        for (int i = 0; it != ie; ++i, ++it)
        {
            push(i, *it);
        }
        
        return *this;        
    }
    
    template <typename K, typename T>
    JsonStream &push(const K &key, const std::vector<T> &val)
    {
        JsonStream stream(_value[key]);
        stream.push(val);
        return *this;
    }
    
    template <typename K, typename T>
    JsonStream &push(const K &key, const std::set<T> &val)
    {
        JsonStream stream(_value[key]);
        stream.push(val);
        return *this;
    }
    
    template <typename K, int SIZE, typename T>
    JsonStream &push(const K &key, const T (&val)[SIZE])
    {
        JsonStream stream(_value[key]);
        for (int i = 0; i < SIZE; ++i)
        {
            stream.push(i, val[i]);
        }
        
        return *this;
    }
    
    //T1 is integer category
    template <typename K, typename T1, typename T2>
    JsonStream &push(const K &key, const std::map<T1, T2> &val)
    {
        JsonStream stream(_value[key]);
        typename std::map<T1, T2>::const_iterator it = val.begin(), ie = val.end();
        for (; it != ie; ++it)
        {
            std::stringstream ss;
            ss << it->first;
            stream.push(ss.str(), it->second);
        }
        return *this;
    }
    
    template <typename K, typename T>
    JsonStream &push(const K &key, const std::map<std::string, T> &val)
    {
        JsonStream stream(_value[key]);
        typename std::map<std::string, T>::const_iterator it = val.begin(), ie = val.end();
        for (; it != ie; ++it)
        {
            stream.push(it->first, it->second);
        }
        return *this;
    }

	template <typename K>
	const JsonStream &pop(const K &key, bool &val) const
	{
		val = _value[key].asBool();
		return *this;
	}
    
    template <typename K>
    const JsonStream &pop(const K &key, int8_t &val) const
    {
        val = _value[key].asInt();
        return *this;
    }
    
    template <typename K>
    const JsonStream &pop(const K &key, uint8_t &val) const
    {
        val = _value[key].asInt();
        return *this;
    }
    
    template <typename K>
    const JsonStream &pop(const K &key, int16_t &val) const
    {
        val = _value[key].asInt();
        return *this;
    }
    
    template <typename K>
    const JsonStream &pop(const K &key, uint16_t &val) const
    {
        val = _value[key].asInt();
        return *this;
    }
    
    template <typename K>
    const JsonStream &pop(const K &key, int32_t &val) const
    {
        val = _value[key].asInt();
        return *this;
    }

    template <typename K>
    const JsonStream &pop(const K &key, uint32_t &val) const
    {
        val = _value[key].asInt();
        return *this;
    }

    template <typename K>
    const JsonStream &pop(const K &key, int64_t &val) const
    {
        val = _value[key].asInt64();
        return *this;
    }
    
    template <typename K>
    const JsonStream &pop(const K &key, uint64_t &val) const
    {
        val = _value[key].asUInt64();
        return *this;
    }
    
    template <typename K>
    const JsonStream &pop(const K &key, float &val) const
    {
    	val = _value[key].asFloat();
        return *this;
    }

    template <typename K>
    const JsonStream &pop(const K &key, double &val) const
    {
    	val = _value[key].asDouble();
        return *this;
    }

    template <typename K>
    const JsonStream &pop(const K &key, std::string &val) const
    {
        val = _value[key].asString();
        return *this;
    }
    
    template <typename K, typename T1, typename T2>
    const JsonStream &pop(const K &key, std::pair<T1, T2> &pair) const
    {
        Json::Value &value = _value[key];
        if (!value.isArray() && value.size()!=2) return *this;
        
        JsonStream stream(value);
        stream.pop(0, pair.first);
        stream.pop(1, pair.second);
        
        return *this;
    }
    
    template <typename K>
    const JsonStream &pop(const K &key, JsonStreamObj &val) const
    {
        JsonStream stream(_value[key]);
        val.decode(stream);
        return *this;
    }
    
    template <typename K>
    const JsonStream &pop(const K &key, Json::Value &value) const
    {
        value = _value[key];
        return *this;
    }
    
    template <typename T>
    const JsonStream &pop(std::vector<T> &val) const
    {
        if (!_value.isArray()) return *this;
        
        uint32_t count = (uint32_t)_value.size();
        for (int i = 0; i < count; ++i)
        {
            val.push_back(T());
            pop(i, val.back());
        }
        return *this;
    }
    
    template <typename K, typename T>
    const JsonStream &pop(const K &key, std::vector<T> &val) const
    {
        JsonStream stream(_value[key]);
        stream.pop(val);
        return *this;
    }
    
    template <typename T>
    const JsonStream &pop(std::set<T> &val) const
    {
        if (!_value.isArray()) return *this;
        
        uint32_t count = (uint32_t)_value.size();
        for (uint32_t i = 0; i < count; ++i)
        {
            T t;
            pop(i, t);
            val.insert(t);
        }
        return *this;
    }
    
    template <typename K, typename T>
    const JsonStream &pop(const K &key, std::set<T> &val) const
    {
        JsonStream stream(_value[key]);
        stream.pop(val);
        return *this;
    }
    
    //T1 is integer category
    template <typename K, typename T1, typename T2>
    const JsonStream &pop(const K &key, std::map<T1, T2> &val) const
    {
        Json::Value &value = _value[key];
        if (!value.isObject() && !value.isArray()) return *this;
        
        JsonStream stream(value);
        if (value.isObject())
        {
            const Json::Value::Members &keys = value.getMemberNames();
            uint32_t keyCount = (uint32_t)keys.size();
            for (int i = 0; i < keyCount; ++i)
            {
                T1 k = (T1)atoi(keys[i].c_str());
                stream.pop(keys[i], val[k]);
            }
        }
        else    //isarray
        {
            T1 count = value.size();
            for (T1 i = 0; i < count; ++i)
            {
                stream.pop(i, val[i]);
            }
        }
        return *this;
    }
    
    template <typename K, typename T>
    const JsonStream &pop(const K &key, std::map<std::string, T> &val) const
    {
        Json::Value &value = _value[key];
        if (!value.isObject()) return *this;
        
        JsonStream stream(value);
        const Json::Value::Members &keys = value.getMemberNames();
        uint32_t keyCount = (uint32_t)keys.size();
        for (uint32_t i = 0; i < keyCount; ++i)
        {
            stream.pop(keys[i], val[keys[i]]);
        }
        return *this;
    }
    
    template <typename K, int SIZE, typename T>
    const JsonStream &pop(const K &key, T (&val)[SIZE]) const
    {
        Json::Value &value = _value[key];
        if (!value.isArray()) return *this;
        
        JsonStream stream(value);
        for (int i = 0; i < SIZE; ++i)
        {
            stream.pop(i, val[i]);
        }
        return *this;
    }
    
    void swap(JsonStream &rhs)
    {
        _value.swap(rhs._value);
    }
private:
    Json::Value &_value;
};
};

#endif
