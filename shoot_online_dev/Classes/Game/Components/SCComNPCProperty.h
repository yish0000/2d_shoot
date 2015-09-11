/*
* ------------------------------------------------------------------------
*  Name:   SCComNPCProperty.h
*  Desc:   ��һ�NPC����
*  Author: umiringo
*  Date:   2015/6/30
* ------------------------------------------------------------------------
*/
#ifndef __SC_COMNPCPROPERTY_H__
#define __SC_COMNPCPROPERTY_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"
#include "../common/message.h"

struct scComNPCPropertyData
{
	std::string name;
	int max_hp;
};

class SCComNPCProperty : public SCComponentBase
{
public:
    SCComNPCProperty() : SCComponentBase(SC_COMPONENT_NPC_PROPERTY), hp(1), isZombie(false) {}
    SCComNPCProperty(scComNPCPropertyData &data);
    virtual ~SCComNPCProperty() {}

    virtual bool init();
    virtual void update(float dt);

    bool IsZombie() { return isZombie; }

    void HandleAttackMsg(attack_msg &msg);

protected:
    std::string name;
    int max_hp; // �������

    int hp; // ����ֵ
    bool isZombie;

private:
    void OnDamage(int damage);
    void OnDeath();
};

#endif