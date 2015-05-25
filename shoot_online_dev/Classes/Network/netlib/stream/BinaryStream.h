#ifndef _SC_BinaryStream_h
#define _SC_BinaryStream_h

#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdint.h>

namespace scnet
{

class BinaryStream;
class BinaryStreamObj
{
public:
    virtual ~BinaryStreamObj() {}
    
protected:
    virtual void encode(BinaryStream &stream) const = 0;
    virtual void decode(const BinaryStream &stream) = 0;
    
    friend class BinaryStream;
};

class BinaryStreamException {};
class BinaryStream : public BinaryStreamObj
{
    void verifyRemainingBytes(int32_t needBytes) const
    {
         if (remainingBytes() < needBytes)
             throw BinaryStreamException();
    }
    
protected:
    template <typename T>
    BinaryStream &push(T val)
    {
        _data.append((const char *)&val, sizeof(val));
        return *this;
    }
    
    template <typename T>
    const BinaryStream &pop(T &val) const
    {
        verifyRemainingBytes(sizeof(val));
        val = *(T *)(_data.data()+_rpos);
        _rpos += sizeof(val);
        return *this;
    }
    
    int remainingBytes() const
    {
        return _data.size()-_rpos;
    }
    
public:
    explicit BinaryStream(const std::string &data=std::string()):_data(data),_rpos(0)
    {}
    
    const std::string &data() const
    {
        return _data;
    }
    
    const BinaryStream &beginRead() const
    {
        _rpos = 0;
        return *this;
    }
    
    virtual void encode(BinaryStream &stream) const
    {
        stream << _data;
    }
    
    virtual void decode(const BinaryStream &stream)
    {
        stream >> _data;
    }
    
    BinaryStream &operator <<(bool val)
    {
        return push(val);
    }
    
    const BinaryStream &operator >>(bool &val) const
    {
        return pop(val);
    }
    
    BinaryStream &operator <<(int8_t val)
    {
        return push(val);
    }
    
    const BinaryStream &operator >>(int8_t &val) const
    {
        return pop(val);
    }
    
    BinaryStream &operator <<(uint8_t val)
    {
        return push(val);
    }
    
    const BinaryStream &operator >>(uint8_t &val) const
    {
        return pop(val);
    }
    
    BinaryStream &operator <<(int16_t val)
    {
        return push(val);
    }
    
    const BinaryStream &operator >>(int16_t &val) const
    {
        return pop(val);
    }
    
    BinaryStream &operator <<(uint16_t val)
    {
        return push(val);
    }
    
    const BinaryStream &operator >>(uint16_t &val) const
    {
        return pop(val);
    }
    
    BinaryStream &operator <<(int32_t val)
    {
        return push(val);
    }
    
    const BinaryStream &operator >>(int32_t &val) const
    {
        return pop(val);
    }
    
    BinaryStream &operator <<(uint32_t val)
    {
        return push(val);
    }
    
    const BinaryStream &operator >>(uint32_t &val) const
    {
        return pop(val);
    }
    
    BinaryStream &operator <<(int64_t val)
    {
        return push(val);
    }
    
    const BinaryStream &operator >>(int64_t &val) const
    {
        return pop(val);
    }
    
    BinaryStream &operator <<(uint64_t val)
    {
        return push(val);
    }
    
    const BinaryStream &operator >>(uint64_t &val) const
    {
        return pop(val);
    }
    
    BinaryStream &operator <<(float val)
    {
    	return push(val);
    }

    const BinaryStream &operator >>(float &val) const
    {
    	return pop(val);
    }

    BinaryStream &operator <<(double val)
    {
    	return push(val);
    }

    const BinaryStream &operator >>(double &val) const
    {
    	return pop(val);
    }

    BinaryStream &operator <<(const std::string &val)
    {
        *this << (uint32_t)val.size();
        _data += val;
        return *this;
    }
    
    BinaryStream &operator <<(const char *val)
    {
        *this << std::string(val);
        return *this;
    }
    
    const BinaryStream &operator >>(std::string &val) const
    {
        verifyRemainingBytes(sizeof(uint32_t));
        uint32_t sz;
        *this >> sz;
        verifyRemainingBytes(sz);
        val.append(_data.data()+_rpos, sz);
        _rpos += sz;
        return *this;
    }
    
    BinaryStream &operator <<(const BinaryStreamObj &val)
    {
        val.encode(*this);
        return *this;
    }
    
    const BinaryStream &operator >>(BinaryStreamObj &val) const
    {
        val.decode(*this);
        return *this;
    }
    
    template <typename T>
    BinaryStream &operator <<(const std::vector<T> &val)
    {
        uint32_t count = (uint32_t)val.size();
        *this << count;
        
        for (uint32_t i = 0; i < count; ++i)
        {
            *this << val[i];
        }
        
        return *this;
    }
    
    template <typename T>
    const BinaryStream &operator >>(std::vector<T> &val) const
    {
        verifyRemainingBytes(sizeof(uint32_t));
        uint32_t count;
        *this >> count;
        
        if (count)
        {
            val.resize(count);
            for (uint32_t i = 0; i < count; ++i)
            {
                *this >> val[i];
            }
        }
        
        return *this;
    }
    
    template <typename T>
    BinaryStream &operator <<(const std::set<T> &val)
    {
        *this << (uint32_t)val.size();
        
        typename std::set<T>::const_iterator it = val.begin(), ie = val.end();
        for (; it != ie; ++it)
        {
            *this << *it;
        }
        
        return *this;
    }
    
    template <typename T>
    const BinaryStream &operator >>(std::set<T> &val) const
    {
        verifyRemainingBytes(sizeof(uint32_t));
        uint32_t count;
        *this >> count;
        
        if (count)
        {
            for (uint32_t i = 0; i < count; ++i)
            {
                T t;
                *this >> t;
                val.insert(t);
            }
        }
        
        return *this;
    }
    
    template <typename K, typename V>
    BinaryStream &operator <<(const std::map<K, V> &val)
    {
        *this << (uint32_t)val.size();
        
        typename std::map<K, V>::const_iterator it = val.begin(), ie = val.end();
        for (; it != ie; ++it)
        {
            *this << it->first << it->second;
        }
        
        return *this;
    }
    
    template <typename K, typename V>
    const BinaryStream &operator >>(std::map<K, V> &val) const
    {
        verifyRemainingBytes(sizeof(uint32_t));
        uint32_t count;
        *this >> count;
        
        if (count)
        {
            for (uint32_t i = 0; i < count; ++i)
            {
                K k;
                *this >> k;
                *this >> val[k];
            }
        }
        
        return *this;
    }
    
    friend bool operator < (const BinaryStream &lhs, const BinaryStream &rhs)
    {
        return lhs._data.compare(rhs._data)<0;
    }
    
    void swap(BinaryStream &rhs)
    {
        _data.swap(rhs._data);
        std::swap(_rpos, rhs._rpos);
    }
protected:
    std::string _data;
    mutable size_t _rpos;
};

}

#endif
