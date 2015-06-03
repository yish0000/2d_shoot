/*
 * ------------------------------------------------------------------------
 *  Name:   SCComPlayerMove.cpp
 *  Desc:   玩家移动组件
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCObject.h"
#include "SCComPlayerMove.h"
#include "SCComCollider.h"
#include "SCComPlayerFSM.h"
 
SCComPlayerMove::SCComPlayerMove()
	: SCComponentBase(SC_COMPONENT_PLAYERMOVE)
{
	m_fMoveSpeed = 300.0f;
	m_fInitJumpHeight = 600.0f;
	m_fGravity = -1400.0f;

	m_fXSpeed = 0.0f;
	m_fYSpeed = 0.0f;
	m_fXAccelerate = 0.0f;
	m_fYAccelerate = -980.0f;
	m_fXDirection = 0.0f;
	m_fYDirection = 0.0f;
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
}