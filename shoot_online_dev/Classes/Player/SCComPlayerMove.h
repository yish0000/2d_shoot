/*
 * ------------------------------------------------------------------------
 *  Name:   SCComPlayerMove.h
 *  Desc:   玩家移动组件
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COMPLAYERMOVE_H__
#define __SC_COMPLAYERMOVE_H__

#include "SCComponentBase.h"

class SCComCollider;
class SCComPlayerFSM;

class SCComPlayerMove : public SCComponentBase
{
public:
	SCComPlayerMove();
	virtual ~SCComPlayerMove();

	virtual bool init();
	virtual void update(float dt);

	void setSpeedX(float speed) { m_fXSpeed = speed; }
	void setSpeedY(float speed) { m_fYSpeed = speed; }
	void setAccelerateX(float accel) { m_fXAccelerate = accel; }
	void setAccelerateY(float accel) { m_fYAccelerate = accel; }

protected:
	float m_fMoveSpeed;
	float m_fInitJumpHeight;
	float m_fGravity;

	float m_fXDirection;
	float m_fYDirection;
	float m_fXSpeed;
	float m_fYSpeed;
	float m_fXAccelerate;
	float m_fYAccelerate;

	SCComCollider* m_pComCollider;
	SCComPlayerFSM* m_pComFSM;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMPLAYERMOVE_H__