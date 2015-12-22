/*
* ------------------------------------------------------------------------
*  Name:   SCComWeapon.cpp
*  Desc:   武器类，用于产生子弹
*  Author: umiringo
*  Date:   2015/6/30
* ------------------------------------------------------------------------
*/

#include "SCComWeapon.h"
#include "SCComArmature.h"
#include "SCComPlayerFSM.h"
#include "../SCWorld.h"
#include "../common/message.h"
#include "Utility/SCUtilityFunc.h"
#include "Data/SCDataModule.h"

USING_NS_CC;

SCComWeapon::SCComWeapon()
	: SCComponentBase(SC_COMPONENT_WEAPON)
	, m_atk_interval(1000), m_bullet_id(SC_INVALID_TID), m_durative(false)
	, m_attacking(false)
{
	m_cntAttack.setPeriod((float)m_atk_interval / 1000.0f);
	m_cntAttack.reset();
}

SCComWeapon::SCComWeapon(int bullet_id)
	: SCComponentBase(SC_COMPONENT_WEAPON), m_bullet_id(SC_INVALID_TID), m_attacking(false)
{
	setBulletID(bullet_id);
}

bool SCComWeapon::init()
{
    return true;
}

void SCComWeapon::update(float dt)
{
	if (m_durative && m_attacking)
	{
		if (m_cntAttack.incCounter(dt))
		{
			doAttack();
			m_cntAttack.reset();
		}
	}
	else
	{
		m_cntAttack.incCounter(dt);
	}
}

void SCComWeapon::attackBegin()
{
	if (m_durative && m_cntAttack.isFull())
	{
		m_attacking = true;
		m_cntAttack.reset(true);
	}
}

void SCComWeapon::attackEnd()
{
	m_attacking = false;
}

void SCComWeapon::attackOnce()
{
	if (m_cntAttack.isFull())
	{
		doAttack();
		m_cntAttack.reset();
	}
}

void SCComWeapon::doAttack()
{
	if (getObject()->isHostPlayer())
	{
		SCComPlayerFSM* pPlayerFSM = dynamic_cast<SCComPlayerFSM*>(getObject()->getComponent(SC_COMPONENT_PLAYERFSM));
		pPlayerFSM->doAttack();

		Point bulletPos;
		SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getObject()->getComponent(SC_COMPONENT_ARMATURE));
		if (pArmature)
		{
			Point vBulletPos;
			if (!pArmature->getBoneWorldPos("qiangkou", vBulletPos))
			{
				vBulletPos = getObject()->getPosition();
				if (getObject()->getFaceDirection() > 0)
					vBulletPos += Point(80, 40);
				else
					vBulletPos += Point(-80, 40);
			}

			const PLAYER_ESSENCE* pEssence = dynamic_cast<SCHostPlayer*>(getObject())->getEssence();
			glb_getWorld()->GenerateBullet(pEssence->orig_bullet_id, vBulletPos, getObject());
		}
	}
}

void SCComWeapon::setAttackInterval(int interval)
{
	m_atk_interval = interval;
	m_cntAttack.setPeriod((float)m_atk_interval / 1000.0f);
}

void SCComWeapon::setBulletID(int bullet_id)
{
	if (bullet_id != m_bullet_id)
	{
		BULLET_ESSENCE* pEssence = (BULLET_ESSENCE*)glb_getDataModule()->getTemplate(bullet_id, DT_BULLET_ESSENCE);
		if (pEssence)
		{
			m_bullet_id = bullet_id;

			setAttackInterval(pEssence->atk_interval);
			setDurative(pEssence->durative);
		}
		else
		{
			CCLOG("SCComWeapon::setBulletID, cannot find the specified bullet template(%d)!", bullet_id);
		}
	}
}