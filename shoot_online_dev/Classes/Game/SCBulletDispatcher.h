
#ifndef __ShootOnline__SCBulletDispatcher__
#define __ShootOnline__SCBulletDispatcher__

#include <stdio.h>
#include "Game/common/mvc.h"

class SCBulletDispatcher : public Dispatcher
{
public:
    SCBulletDispatcher(SCObject* pObj) : Dispatcher(pObj) {}
    virtual ~SCBulletDispatcher() {}

public:
    void SendAttackMessage(GID target, int atk_max, int atk_min);
};

#endif