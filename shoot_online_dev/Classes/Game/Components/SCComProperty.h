/*
* ------------------------------------------------------------------------
*  Name:   SCComProperty.h
*  Desc:   ��һ�NPC����
*  Author: umiringo
*  Date:   2015/6/30
* ------------------------------------------------------------------------
*/
#ifndef __SC_COMPROPERTY_H__
#define __SC_COMPROPERTY_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"
#include "../common/message.h"

class SCComProperty : public SCComponentBase
{
public:
    SCComProperty() : SCComponentBase(SC_COMPONENT_PROPERTY), hp(1), isZombie(false) {}
    SCComProperty(scComPropertyData &data);
    virtual ~SCComProperty() {}

    virtual bool init();
    virtual void update(float dt);

    bool IsZombie() { return isZombie; }

    void HandleAttackMsg(attack_msg &msg);
protected:
    int max_hp; // �������
    int atk_mode;
    int atk_interval;
    int bullet_id;
   
    int hp; // ����ֵ
    bool isZombie;

private:
    void OnDamage(int damage);
    void OnDeath();
};

#endif