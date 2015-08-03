/*
 * ------------------------------------------------------------------------
 *  Name:   SCComNPCMove.h
 *  Desc:   负责NPC移动的组件
 *  Author: Yish
 *  Date:   2015/8/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COMNPCMOVE_H__
#define __SC_COMNPCMOVE_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"

class SCComCollider;
class SCComNPCFSM;

class SCComNPCMove : public SCComponentBase
{
public:
	SCComNPCMove();
	virtual ~SCComNPCMove();

	virtual bool init();
	virtual void update(float dt);

	void setSpeedX(float speed) { m_fXSpeed = speed; }
	void setSpeedY(float speed) { m_fYSpeed = speed; }
	void setAccelerateX(float accel) { m_fXAccelerate = accel; }
	void setAccelerateY(float accel) { m_fYAccelerate = accel; }

	// 获取碰撞检测结果
	const SCWorld::CollisionResult& getCollisionResult() const { return m_collisionResult; }

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
	SCComNPCFSM* m_pComFSM;
	SCWorld::CollisionResult m_collisionResult;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMNPCMOVE_H__