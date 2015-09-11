/*
* ------------------------------------------------------------------------
*  Name:   SCComWeapon.h
*  Desc:   �����࣬���ڲ����ӵ�
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
    int m_bullet_id;		// �ӵ�ģ��ID
    int m_atk_interval;		// ���Ƶ��(����)
	bool m_durative;		// �Ƿ�������
	bool m_attacking;		// ���������
	SCCounter m_cntAttack;	// ������Ƶ��

	void doAttack();
};

#endif