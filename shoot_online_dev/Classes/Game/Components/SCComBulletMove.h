#ifndef __SC_COMBULLETMOVE_H__
#define __SC_COMBULLETMOVE_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"

struct scComBulletMoveData
{
	int speed;
	cocos2d::Point birthPos;
};

class SCComCollider;

class SCComBulletMove : public SCComponentBase
{
public:
    SCComBulletMove() : SCComponentBase(SC_COMPONENT_BULLET_MOVE) {}
    SCComBulletMove(scComBulletMoveData& data);
    virtual ~SCComBulletMove() {}
    virtual bool init();
    virtual void update(float dt);

public:
    int speed;
    int live_time;
    cocos2d::Point birth_pos;
};

#endif