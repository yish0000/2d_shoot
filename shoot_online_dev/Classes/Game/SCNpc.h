#ifndef __SCNPC_H__
#define __SCNPC_H__

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
    virtual bool init();
    CREATE_FUNC(SCNpc)

public:
    virtual int DispatchMessage(const Message& msg);
};


#endif //__SCNPC_H__