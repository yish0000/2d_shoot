/*
 * ------------------------------------------------------------------------
 *  Name:   SCComNPCFSM.h
 *  Desc:   NPC×´Ì¬»ú
 *  Author: Yish
 *  Date:   2015/8/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COMNPCFSM_H__
#define __SC_COMNPCFSM_H__

#include "SCComponentBase.h"

class SCComNPCFSM : public SCComponentBase
{
public:

	enum
	{
		STATE_STAND,
		STATE_MOVE,
		STATE_JUMP,
	};

public:
	SCComNPCFSM();
	virtual ~SCComNPCFSM();

	virtual bool init();
	virtual void update(float dt);

	void doStand(bool afterJump = false);
	void doRun();
	void doJump(float fInitSpeedY);
	void doAttack();

	int getCurState() const { return m_iState; }

protected:
	int m_iState;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMNPCFSM_H__