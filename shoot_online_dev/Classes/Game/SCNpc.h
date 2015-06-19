#ifndef __LOGIC_NPC_H__
#define __LOGIC_NPC_H__

#include "SCObject.h"
#include <string>
#include "SCNpcController.h"
#include "SCNpcDispatcher.h"

class SCNpc : public SCObject
{
private:
	//此处定义基本属性

public:
    SCNpcController* _controller;
    SCNpcDispatcher* _dispatcher;
public:
	SCNpc() {}
	virtual ~SCNpc() {}
    
    CREATE_FUNC(SCNpc)

public:
    virtual int DispatchMessage(const Message& msg);
};


#endif //__LOGIC_NPC_H__