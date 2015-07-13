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
#include "../SCObject.h"

//处理消息以及分发
class Controller
{
private:
    SCObject *m_pObject;
public:
    Controller(SCObject* pObj) : m_pObject(pObj)
    {}
    virtual ~Controller() {}
    
    virtual int MessageHandler(const Message& msg) = 0;

	SCObject* getObject() const { return m_pObject; }
};

//发送消息模块函数打包处
class Dispatcher
{
private:
    SCObject *m_pObject;
public:
    Dispatcher(SCObject* pObj) : m_pObject(pObj)
    {}
    virtual ~Dispatcher(){}

	SCObject* getObject() const { return m_pObject; }
};


#endif
