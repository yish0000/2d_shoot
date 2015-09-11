/*
* ------------------------------------------------------------------------
*  Name:   SCComWeapon.h
*  Desc:   武器类，用于产生子弹
*  Author: umiringo
*  Date:   2015/6/30
* ------------------------------------------------------------------------
*/

#ifndef __SC_COMWEAPON_H__
#define __SC_COMWEAPON_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"
#include "../common/message.h"
#include "Utility/SCCounter.h"

class SCComWeapon : public SCComponentBase
{
public:
	SCComWeapon();
	SCComWeapon(int bullet_id);
    virtual ~SCComWeapon() {}

    virtual bool init();
    virtual void update(float dt);

	void attackOnce();
	void attackBegin();
	void attackEnd();

	int getBulletID() const { return m_bullet_id; }
	int getAttackInterval() const { return m_atk_interval; }

	void setBulletID(int bullet_id);
	void setAttackInterval(int interval);
	void setDurative(bool durative) { m_durative = durative; }

private:
    int m_bullet_id;		// 子弹模板ID
    int m_atk_interval;		// 射击频率(毫秒)
	bool m_durative;		// 是否持续射击
	bool m_attacking;		// 正在射击中
	SCCounter m_cntAttack;	// 检测射击频率

	void doAttack();
};

#endif