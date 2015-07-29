/*
* ------------------------------------------------------------------------
*  Name:   SCComProperty.cpp
*  Desc:   ��һ�NPC����
*  Author: umiringo
*  Date:   2015/6/30
* ------------------------------------------------------------------------
*/
#include "SCComProperty.h"
#include "Utility/SCRandomGen.h"

SCComProperty::SCComProperty(scComPropertyData &data)
{
    max_hp = data.max_hp;
    atk_mode = data.atk_mode;
    atk_interval = data.atk_mode;
    bullet_id = data.bullet_id;

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
    }
}

void SCComProperty::OnDeath()
{
    isZombie = true;
    //��������
}
