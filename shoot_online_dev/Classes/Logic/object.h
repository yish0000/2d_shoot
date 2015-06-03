/*
* ------------------------------------------------------------------------
*  Name:  	object.h
*  Desc:   object对象
*  Author: umiringo
*  Date:   2015/6/2
* ------------------------------------------------------------------------
*/

#ifndef __LOGIC__OBJECT_H__
#define __LOGIC__OBJECT_H__

#include <Common/SCThread.h>
#include <Logic/common/type.h>
#include "cocos2d.h"

#include "config.h"


class GameObject
{
private:
	SCMutex lock;
	GID id;
	cocos2d::Vec2 pos;

public:
	GameObject() {}
	~GameObject() {}
};

#endif //__LOGIC__OBJECT_H__
