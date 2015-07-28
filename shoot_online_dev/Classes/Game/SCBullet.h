#ifndef __SCBULLET_H__
#define __SCBULLET_H__

#include "SCObject.h"
#include <string>
#include "SCBulletController.h"
#include "SCBulletDispatcher.h"

class SCBullet : public SCObject
{
private:
    //此处定义基本属性

public:
    SCBulletController* _controller;
    SCBulletDispatcher* _dispatcher;
public:
    SCBullet(GID gid, int tid) :SCObject(gid, tid) {}
    SCBullet() {}
    virtual ~SCBullet();
    virtual bool init();
    CREATE_FUNC(SCBullet)

public:
    virtual int DispatchMessage(const Message& msg);
};


#endif //__SCBullet_H__