#include "SCComPlayerProperty.h"
#include "SCComArmature.h"
#include "SCComPlayerMove.h"
#include "../SCGameModule.h"
#include "Utility/SCRandomGen.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;

SCComPlayerProperty::SCComPlayerProperty(scComPlayerPropertyData &data)
:SCComponentBase(SC_COMPONENT_PLAYER_PROPERTY)
{
    max_hp = data.max_hp;
    name = data.name;

    hp = max_hp;
    isZombie = false;
}

bool SCComPlayerProperty::init()
{
    //应该从存档中读取
    return true;
}

void SCComPlayerProperty::update(float dt)
{
    if (isZombie)
        return;
    if (hp <= 0)
    {
        OnDeath();
        return;
    }
}

void SCComPlayerProperty::HandleAttackMsg(attack_msg& atk_msg)
{
    if (isZombie) return;
    int damage = SCRandomGen::RandomInt(atk_msg.damage_low, atk_msg.damage_high);
    OnDamage(damage);
}

void SCComPlayerProperty::OnDamage(int damage)
{
    if (damage > 0 && hp > 0)
    {
        hp -= damage;

		if (hp <= 0)
		{
			hp = 0;
			OnDeath();
		}
        else
        {
            SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getObject()->getComponent(SC_COMPONENT_ARMATURE));
            if (pArmature)
            {
                pArmature->playAnimation("shoushang", false, true, pArmature->getCurAnimName());
            }

			Sequence* pAction = Sequence::create(Blink::create(1.0f, 10), Show::create(), nullptr);
			getObject()->runAction(pAction);
        }
    }
}

void SCComPlayerProperty::OnDeath()
{
    isZombie = true;

    SCComPlayerMove* pMove = dynamic_cast<SCComPlayerMove*>(m_pGameObj->getComponent(SC_COMPONENT_PLAYERMOVE));
    if (pMove)
        pMove->die();

    m_pGameObj->setActive(false);

	glb_getGameModule()->dispatchEvent(SC_EVENT_STAGE_CLEAR);
}
