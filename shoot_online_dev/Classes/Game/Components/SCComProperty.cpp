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
#include "Utility/SCRandomGen.h"

SCComProperty::SCComProperty(scComPropertyData &data)
	: SCComponentBase(SC_COMPONENT_PROPERTY)
{
    max_hp = data.max_hp;
    atk_mode = data.atk_mode;
    atk_interval = data.atk_mode;
    bullet_id = data.bullet_id;
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
    if (isZombie) return;
    if (hp <= 0)
    {
        OnDeath();
        return;
    }
    heartbeatCount += dt;
    if (heartbeatCount > atk_interval)
    {
        AIAttack();
        heartbeatCount = 0;
    }

}

void SCComProperty::HandleAttackMsg(attack_msg& atk_msg)
{
    if (isZombie) return;
    int damage = SCRandomGen::RandomInt(atk_msg.damage_low, atk_msg.damage_high);
  //  if (SCRandomGen::RandomUniform() < atk_msg.crit_rate)
   // {
   //     damage = damage * atk_msg.crit_ratio / 100;
  //  }

    OnDamage(damage);
}

void SCComProperty::OnDamage(int damage)
{
    if (damage > 0)
    {
        hp -= damage;

		if (hp <= 0)
			OnDeath();
		else
		{
			SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getObject()->getComponent(SC_COMPONENT_ARMATURE));
			if (pArmature)
				pArmature->playAnimation("shoushang", false);
		}
    }
}

void SCComProperty::OnDeath()
{
    isZombie = true;
    //死亡动画

	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(m_pGameObj->getComponent(SC_COMPONENT_ARMATURE));
	if (pArmature)
		pArmature->playAnimation("siwang", false);
}

void SCComProperty::AIAttack()
{
    SCNpc *object = dynamic_cast<SCNpc *>(m_pGameObj);
	if (object)
	{
		SCWorld* pWorld = object->getWorld();
		if (pWorld) pWorld->GenerateBullet(bullet_id, fire_pos);
	}
}