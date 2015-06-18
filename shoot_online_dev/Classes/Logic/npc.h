#ifndef __LOGIC_NPC_H__
#define __LOGIC_NPC_H__

#include "object.h"
#include <string>
#include "world.h"

class NpcObject : public GameObject
{
private:
	//此处定义基本属性

	//需要定义controller和viewer部分

public:
	NpcObject() {}
	virtual ~NpcObject() {}
};

#endif //__LOGIC_NPC_H__