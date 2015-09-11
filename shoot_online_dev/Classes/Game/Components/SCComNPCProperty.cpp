/*
* ------------------------------------------------------------------------
*  Name:   SCComNPCProperty.cpp
*  Desc:   玩家或NPC属性
*  Author: umiringo
*  Date:   2015/6/30
* ------------------------------------------------------------------------
*/
#include "SCComNPCProperty.h"
#include "SCComArmature.h"
#include "SCComNPCAI.h"
#include "../SCGameModule.h"
#include "Utility/SCRandomGen.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;

SCComNPCProperty::SCComNPCProperty(scComNPCPropertyData &data)
: SCComponentBase(SC_COMPONENT_NPC_PROPERTY)
{
    max_hp = data.max_hp;
    name = data.name;

    hp = max_hp;
    isZombie = false;
}

bool SCComNPCProperty::init()
{
    return true;
}

void SCComNPCProperty::update(float dt)
{
    if (isZombie)
        return;

    if (hp <= 0)
    {
        OnDeath();
        return;
    }
}

void SCComNPCProperty::HandleAttackMsg(attack_msg& atk_msg)
{
    if (isZombie) return;
    int damage = SCRandomGen::RandomInt(atk_msg.damage_low, atk_msg.damage_high);
    OnDamage(damage);
}

void SCComNPCProperty::OnDamage(int damage)
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
				if (getObject()->getTID() == 726) //? by cy
					pArmature->playAnimation("shoushang1", false, true, "zhanli");
				else
					pArmature->playAnimation("shoushang", false, true, "zhanli");
			}
		}
    }
}

void SCComNPCProperty::OnDeath()
{
    isZombie = true;

    //死亡动画
	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(m_pGameObj->getComponent(SC_COMPONENT_ARMATURE));
	if (pArmature)
		pArmature->playAnimation("siwang", false);

    //调用AI的死亡接口
    SCComNPCAI* pNPCAI = dynamic_cast<SCComNPCAI*>(m_pGameObj->getComponent(SC_COMPONENT_NPCAI));
    if (pNPCAI)
        pNPCAI->onDeath();

	// 临时代码
	// 如果是BOSS，播放慢镜头效果，触发过关事件
	if (getObject()->getTID() == 726)
	{
		glb_getGameModule()->playTimeScaleEffect();
		glb_getGameModule()->dispatchEvent(SC_EVENT_STAGE_CLEAR);
	}

    m_pGameObj->setActive(false);

	// 一秒之后，销毁尸体
	bool bDispear = dynamic_cast<SCNpc*>(getObject())->getEssence()->is_dispear;
	if (bDispear)
	{
		dynamic_cast<SCNpc*>(getObject())->doDispear(1.0f);
	}
}