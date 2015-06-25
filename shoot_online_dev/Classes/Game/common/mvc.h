//
//  controller.h
//  ShootOnline
//
//  Created by 琰 陈 on 15/6/18.
//
//

#ifndef ShootOnline_controller_h
#define ShootOnline_controller_h

#include <Game/common/message.h>
#include "SCObject.h"

class GameObject;

//处理消息以及分发
class Controller
{
private:
    SCObject *obj;
public:
    Controller():obj(nullptr)
    {}
    virtual ~Controller(){}
    
    virtual int MessageHandler(const Message& msg) = 0;
    
    
};

//发送消息模块函数打包处
class Dispatcher
{
private:
    SCObject *obj;
public:
    Dispatcher():obj(nullptr)
    {}
    virtual ~Dispatcher(){}
};


#endif
