/*
 * ------------------------------------------------------------------------
 *  Name:   SCComPlayerFSM.h
 *  Desc:   主玩家状态机
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COMPLAYERFSM_H__
#define __SC_COMPLAYERFSM_H__

#include "SCComponentBase.h"

class SCComArmature;

class SCComPlayerFSM : public SCComponentBase
{
public:

	enum
	{
		STATE_STAND,
		STATE_MOVE,
		STATE_JUMP,
        STATE_DIE,
	};

public:
	SCComPlayerFSM();
	virtual ~SCComPlayerFSM();

	virtual bool init();
	virtual void update(float dt);

	void doStand(bool afterJump = false);
	void doRun();
	void doJump(float fInitSpeedY);
	void doAttack();
    void doDie();

	int getCurState() const { return m_iState; }

protected:
	int m_iState;
	SCComArmature* m_pArmature;
	float m_fCurAnimTime;
	float m_fCurAnimTotalTime;

	void update_Stand(float dt);
	void update_Move(float dt);
	void update_Jump(float dt);
    void update_Die(float dt);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMPLAYERFSM_H__