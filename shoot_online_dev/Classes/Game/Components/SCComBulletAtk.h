#ifndef __SC_COMBULLETATK_H__
#define __SC_COMBULLETATK_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"
#include "../common/message.h"

struct scComBulletAtkData
{
	int atk_max;
	int atk_min;
};

class SCComBulletAtk : public SCComponentBase
{
public:
	SCComBulletAtk() : SCComponentBase(SC_COMPONENT_BULLET_ATK), atk_min(0), atk_max(0) {}
    SCComBulletAtk(scComBulletAtkData &data);
    virtual ~SCComBulletAtk() {}

    virtual bool init();
    virtual void update(float dt);

    int atk_min;
    int atk_max;
protected:
    void DoAttack(int64_t target);

private:
    void BuildAttackMessage(Message& msg);
};


#endif