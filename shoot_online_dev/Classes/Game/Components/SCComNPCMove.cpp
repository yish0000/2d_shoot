/*
 * ------------------------------------------------------------------------
 *  Name:   SCNPCMove.cpp
 *  Desc:   负责NPC移动的组件
 *  Author: Yish
 *  Date:   2015/8/3
 * ------------------------------------------------------------------------
 */

#include "../SCObject.h"
#include "SCComNPCMove.h"
#include "SCComCollider.h"
#include "SCComNPCFSM.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;

SCComNPCMove::SCComNPCMove()
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
}

SCComNPCMove::~SCComNPCMove()
{
}

bool SCComNPCMove::init()
{
	m_bActive = true;
	m_pComCollider = dynamic_cast<SCComCollider*>(m_pGameObj->getComponent(SC_COMPONENT_COLLIDER));
	m_pComFSM = dynamic_cast<SCComNPCFSM*>(m_pGameObj->getComponent(SC_COMPONENT_NPCFSM));
	return true;
}

void SCComNPCMove::update(float dt)
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
	if( m_pComFSM->getCurState() == SCComNPCFSM::STATE_STAND )
	{
		if( !collision.bottomCollision )
			m_pComFSM->doJump(0.0f);
		else if( m_fXDirection != 0 )
			m_pComFSM->doRun();
		else
			m_pGameObj->setPosition(newX, collision.bottomCollisionY + 1);
	}
	else if( m_pComFSM->getCurState() == SCComNPCFSM::STATE_MOVE )
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
	else if( m_pComFSM->getCurState() == SCComNPCFSM::STATE_JUMP )
	{
		if( m_fYSpeed < 0.0f && collision.bottomCollision )
		{
			m_pGameObj->setPosition(posOld.x, collision.bottomCollisionY + 1);
			if( m_fXSpeed != 0.0f )
				m_pComFSM->doRun();
			else
				m_pComFSM->doStand(true);
		}
		else
		{
			m_pGameObj->setPosition(newX, newY);
		}
	}
}
