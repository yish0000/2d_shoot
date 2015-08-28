#ifndef __SC_COMPLAYERPROPERTY_H__
#define __SC_COMPLAYERPROPERTY_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"
#include "../common/message.h"

struct scComPlayerPropertyData
{
    std::string name;
    int max_hp;
};

class SCComPlayerProperty : public SCComponentBase
{
public:
    SCComPlayerProperty() : SCComponentBase(SC_COMPONENT_PLAYER_PROPERTY), hp(1), isZombie(false){}
    SCComPlayerProperty(scComPlayerPropertyData &data);
    virtual ~SCComPlayerProperty() {}

    virtual bool init();
    virtual void update(float dt);

    bool IsZombie() { return isZombie; }

    void HandleAttackMsg(attack_msg &msg);

protected:
    std::string name;
    int max_hp; // 最大生命

    int hp; // 生命值
    bool isZombie;

private:
    void OnDamage(int damage);
    void OnDeath();
};

#endif