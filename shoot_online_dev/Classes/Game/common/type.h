#ifndef __LOGIC_COMMON_TYPE_H__
#define __LOGIC_COMMON_TYPE_H__
/*
 * ------------------------------------------------------------------------
 *  Name:   type.h
 *  Desc:   逻辑部分所使用的基本类型的定义
 *  Author: umiringo
 *  Date:   2015/6/1
 * ------------------------------------------------------------------------
 */

#include "base/ccTypes.h"

enum
{
    SC_OBJECT_UNKNOWN,
    
    SC_OBJECT_HOSTPLAYER,
    SC_OBJECT_NPC,
};


class GID //游戏对象ID
{
public:
	int type; //OBJ_TYPE
 	int64_t id;
    
	GID() : type(-1), id(-1) {}
	GID(int _type, int64_t _id) : type(_type), id(_id) {}
	~GID() {}

	inline bool operator==(const GID &rhs) const 
	{
		return type == rhs.type && id == rhs.id;
	}

	inline bool operator!=(const GID &rhs) const
	{
		return type != rhs.id || type != rhs.type;
	}
    
    inline bool IsValid() const
    {
        return type != -1;
    }

};

#endif // __LOGIC_COMMON_TYPE_H__