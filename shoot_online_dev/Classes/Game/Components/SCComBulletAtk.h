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
	SCComBulletAtk() : SCComponentBase(SC_COMPONENT_BULLET_ATK), m_atk_min(0), m_atk_max(0) {}
    SCComBulletAtk(scComBulletAtkData &data);
    virtual ~SCComBulletAtk() {}

    virtual bool init();
    virtual void update(float dt);

	int getAttackMin() const { return m_atk_min; }
	int getAttackMax() const { return m_atk_max; }

	void DoAttack(int64_t target);

protected:
	int m_atk_min;
	int m_atk_max;

private:
    void BuildAttackMessage(Message& msg);
};


#endif