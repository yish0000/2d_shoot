#ifndef __ShootOnline__SCBulletController__
#define __ShootOnline__SCBulletController__

#include <stdio.h>
#include "Game/common/mvc.h"

class SCBullet;

class SCBulletController : public Controller
{
public:
    SCBulletController(SCObject* pObj) : Controller(pObj) {}
    virtual ~SCBulletController() {}

    virtual int MessageHandler(const Message& msg);
};

#endif 
