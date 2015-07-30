/*
* ------------------------------------------------------------------------
*  Name:   SCComProperty.h
*  Desc:   玩家或NPC属性
*  Author: umiringo
*  Date:   2015/6/30
* ------------------------------------------------------------------------
*/
#ifndef __SC_COMPROPERTY_H__
#define __SC_COMPROPERTY_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"
#include "../common/message.h"

struct scComPropertyData
{
	std::string name;
	int max_hp;
	int atk_mode;
	int atk_interval;
	int bullet_id;
};

class SCComProperty : public SCComponentBase
{
public:
    SCComProperty() : SCComponentBase(SC_COMPONENT_PROPERTY), hp(1), isZombie(false),heartbeatCount(0) {}
    SCComProperty(scComPropertyData &data);
    virtual ~SCComProperty() {}

    virtual bool init();
    virtual void update(float dt);

    bool IsZombie() { return isZombie; }

    void HandleAttackMsg(attack_msg &msg);
protected:
    std::string name;
    int max_hp; // 最大生命
    int atk_mode;
    int atk_interval;
    int bullet_id;
   
    int hp; // 生命值
    bool isZombie;
    cocos2d::Point fire_pos;

private:
    void OnDamage(int damage);
    void OnDeath();
    void AIAttack();

    float heartbeatCount;
};

#endif