/*
* ------------------------------------------------------------------------
*  Name:   SCComWeapon.h
*  Desc:   �����࣬���ڲ����ӵ�
*  Author: umiringo
*  Date:   2015/6/30
* ------------------------------------------------------------------------
*/

#ifndef __SC_COMWEAPON_H__
#define __SC_COMWEAPON_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"
#include "../common/message.h"

class SCComWeapon : public SCComponentBase
{
public:
    SCComWeapon() : SCComponentBase(SC_COMPONENT_PROPERTY) {}
    virtual ~SCComWeapon() {}

    virtual bool init();
    virtual void update(float dt);
};

#endif