/*
* ------------------------------------------------------------------------
*  Name:   SCComProperty.cpp
*  Desc:   玩家或NPC属性
*  Author: umiringo
*  Date:   2015/6/30
* ------------------------------------------------------------------------
*/
#include "SCComProperty.h"
#include "SCComArmature.h"
#include "SCComNPCAI.h"
#include "Utility/SCRandomGen.h"

SCComProperty::SCComProperty(scComPropertyData &data)
: SCComponentBase(SC_COMPONENT_PROPERTY), removeCount(-1.0f), isDispear(true)
{
    max_hp = data.max_hp;
    name = data.name;
    
    hp = max_hp;
    isZombie = false;
}

bool SCComProperty::init()
{
    return true;
}

void SCComProperty::update(float dt)
{
    if (isZombie)
    {
        if (removeCount < 0.00001)
            return;
        else if (removeCount >= NPC_REMOVE_COUNTDOWN)
        {
            m_pGameObj->removeFromParent();
            removeCount = -1.0f;
        }
        else
        {
            removeCount += dt;
        }
        return;
    }
    if (hp <= 0)
    {
        OnDeath();
        return;
    }
}

void SCComProperty::HandleAttackMsg(attack_msg& atk_msg)
{
    if (isZombie) return;
    int damage = SCRandomGen::RandomInt(atk_msg.damage_low, atk_msg.damage_high);
    OnDamage(damage);
}

void SCComProperty::OnDamage(int damage)
{
    if (damage > 0 && hp > 0)
    {
        hp -= damage;

		if (hp <= 0)
			OnDeath();
		else
		{
			SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getObject()->getComponent(SC_COMPONENT_ARMATURE));
			if (pArmature)
			{
				if (getObject()->getTID() == 726) //? by cy
					pArmature->playAnimation("shoushang1", false, true, "zhanli");
				else
					pArmature->playAnimation("shoushang", false, true, "zhanli");
			}
		}
    }
}

void SCComProperty::OnDeath()
{
    isZombie = true;
    if (isDispear)
    {
        removeCount = 0.0001f;
    }

    //死亡动画
	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(m_pGameObj->getComponent(SC_COMPONENT_ARMATURE));
	if (pArmature)
		pArmature->playAnimation("siwang", false);

    //调用AI的死亡接口
    /*
    SCComNPCAI* pNPCAI = dynamic_cast<SCComNPCAI*>(m_pGameObj->getComponent(SC_COMPONENT_NPCAI));
    if (pNPCAI)
        pNPCAI->onDeath();
    */
    m_pGameObj->setActive(false);


}
