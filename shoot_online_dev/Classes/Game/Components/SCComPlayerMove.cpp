/*
 * ------------------------------------------------------------------------
 *  Name:   SCComPlayerMove.cpp
 *  Desc:   玩家移动组件
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "../SCObject.h"
#include "SCComPlayerMove.h"
#include "SCComCollider.h"
#include "SCComPlayerFSM.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;
 
SCComPlayerMove::SCComPlayerMove()
	: SCComponentBase(SC_COMPONENT_PLAYERMOVE)
{
	m_fMoveSpeed = 200.0f;
	m_fInitJumpHeight = 200.0f;
	m_fGravity = -1400.0f;

	m_fXSpeed = 0.0f;
	m_fYSpeed = 0.0f;
	m_fXAccelerate = 0.0f;
	m_fYAccelerate = -980.0f;
	m_fXDirection = 0.0f;
	m_fYDirection = 0.0f;

	m_iJumpCount = 0;
}

SCComPlayerMove::~SCComPlayerMove()
{
}

bool SCComPlayerMove::init()
{
	m_bActive = true;
	m_pComCollider = dynamic_cast<SCComCollider*>(m_pGameObj->getComponent(SC_COMPONENT_COLLIDER));
	m_pComFSM = dynamic_cast<SCComPlayerFSM*>(m_pGameObj->getComponent(SC_COMPONENT_PLAYERFSM));
	return true;
}

void SCComPlayerMove::update(float dt)
{
	float fMaxSpeed = 1000.0f;

	SCWorld* pWorld = glb_getWorld();
	SCTiledMap* pMap = pWorld->getTileMap();

	// 更新移动速度
	m_fYSpeed = m_fYSpeed + m_fYAccelerate * dt;
	clampf(m_fYSpeed, -fMaxSpeed, fMaxSpeed);

	// 计算新位置
	Point posOld = m_pGameObj->getPosition();
	float newX = clampf(posOld.x + m_fXSpeed * dt, 0, pMap->getRealWidth());
	float newY = clampf(posOld.y + m_fYSpeed * dt, 0, pMap->getRealHeight() + 200);

	// 检测碰撞
	SCWorld::CollisionResult collision;
	const cocos2d::Rect& bb = m_pComCollider->getSymmetryBoundingBox();
	pWorld->checkCollision(bb, posOld, Point(newX, newY), collision);
	if( collision.rightCollision )
		newX = collision.rightCollisionX - bb.size.width / 2 - 1;
	else if( collision.leftCollision )
		newX = collision.leftCollisionX + bb.size.width / 2 + 1;
	m_collisionResult = collision;

	cocos2d::Rect oldBB = m_pComCollider->getBoundingBox();

	// 更新状态
	if( m_pComFSM->getCurState() == SCComPlayerFSM::STATE_STAND )
	{
		if( !collision.bottomCollision )
			m_pComFSM->doJump(0.0f);
		else if( m_fXDirection != 0 )
			m_pComFSM->doRun();
		else
			m_pGameObj->setPosition(newX, collision.bottomCollisionY + 1);
	}
	else if( m_pComFSM->getCurState() == SCComPlayerFSM::STATE_MOVE )
	{
		if( m_fXDirection == 0.0f )
			m_pComFSM->doStand();
		else if( !collision.bottomCollision )
			m_pComFSM->doJump(0.0f);
		else
		{
			m_fYSpeed = 0.0f;
			m_pGameObj->setPosition(newX, collision.bottomCollisionY + 1);
		}
	}
	else if( m_pComFSM->getCurState() == SCComPlayerFSM::STATE_JUMP )
	{
		if( m_fYSpeed < 0.0f && collision.bottomCollision )
		{
			m_pGameObj->setPosition(posOld.x, collision.bottomCollisionY + 1);
			if( m_fXSpeed != 0.0f )
				m_pComFSM->doRun();
			else
				m_pComFSM->doStand(true);
			m_iJumpCount = 0;
		}
		else
		{
			m_pGameObj->setPosition(newX, newY);
		}
	}
}

void SCComPlayerMove::move(float xDir, float yDir)
{
	// 更新输入方向
	m_fXDirection = xDir;
	m_fYDirection = yDir;

	// 更新移动速度
	setSpeedX(m_fMoveSpeed * m_fXDirection);
	m_iJumpCount = 0;
}

void SCComPlayerMove::jump()
{
	if( m_iJumpCount > 0 )
		return;

	m_iJumpCount++;

	// 跳起的初速度
	float speed = sqrtf(2 * fabs(m_fGravity) * m_fInitJumpHeight);
	m_pComFSM->doJump(speed);

	setSpeedX(m_fMoveSpeed * m_fXDirection);
	setSpeedY(speed);
	setAccelerateY(m_fGravity);
}

void SCComPlayerMove::onMsg_DoFSMEvent(int state)
{
	if( state == SCComPlayerFSM::STATE_STAND )
	{
		setSpeedX(0);
		setSpeedY(0);
		setAccelerateY(0);
		m_iJumpCount = 0;
	}
	else if( state == SCComPlayerFSM::STATE_MOVE )
	{
		setSpeedX(m_fMoveSpeed * m_fXDirection);
		setSpeedY(0);
		setAccelerateY(0);
		m_iJumpCount = 0;
	}
	else if( state == SCComPlayerFSM::STATE_JUMP )
	{
	}
}