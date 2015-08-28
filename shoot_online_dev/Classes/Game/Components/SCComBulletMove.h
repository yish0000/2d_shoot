#ifndef __SC_COMBULLETMOVE_H__
#define __SC_COMBULLETMOVE_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"

struct scComBulletMoveData
{
	int speed;
	cocos2d::Point birthPos;
    int owner_type;
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

	void setSpeed(float fSpeed) { m_speed = fSpeed; }
	void setLiveTime(int liveTime) { m_live_time = liveTime; }
	void setBirthPos(const cocos2d::Point& pos) { m_birth_pos = pos; }
    void setOwnerType(int type) { m_owner_type = type; }

	int getSpeed() const { return m_speed; }
	int getLiveTime() const { return m_live_time; }
	const cocos2d::Point& getBirthPos() const { return m_birth_pos; }
    const int getOwnerType() const { return m_owner_type; }

public:
    int m_speed;
    int m_live_time;
    cocos2d::Point m_birth_pos;
    int m_owner_type;
};

#endif