/*
 * ------------------------------------------------------------------------
 *  Name:   SCComPlayerFSM.cpp
 *  Desc:   主玩家状态机
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "../SCObject.h"
#include "SCComPlayerFSM.h"
#include "SCComArmature.h"

SCComPlayerFSM::SCComPlayerFSM()
	: SCComponentBase(SC_COMPONENT_PLAYERFSM)
{
	m_iState = STATE_STAND;
	m_fCurAnimTime = 0.0f;
}

SCComPlayerFSM::~SCComPlayerFSM()
{
}

bool SCComPlayerFSM::init()
{
	m_bActive = true;
	m_pArmature = dynamic_cast<SCComArmature*>(m_pGameObj->getComponent(SC_COMPONENT_ARMATURE));
	return true;
}

void SCComPlayerFSM::update(float dt)
{
	switch(m_iState)
	{
	case STATE_STAND:
		update_Stand(dt);
		break;
	case STATE_MOVE:
		update_Move(dt);
		break;
	case STATE_JUMP:
		update_Jump(dt);
		break;
	}
}

void SCComPlayerFSM::doStand(bool afterJump /* = false */)
{
	if( afterJump )
	{
		m_pArmature->playAnimation("luodi", false);
		m_fCurAnimTime = 0.0f;
		m_fCurAnimTotalTime = 0.5f;
	}
	else
		m_pArmature->playAnimation("zhanli", true);
	m_iState = STATE_STAND;
}

void SCComPlayerFSM::doRun()
{
	m_iState = STATE_MOVE;
	m_pArmature->playAnimation("benpao", true);
}

void SCComPlayerFSM::doJump(float fInitSpeedY)
{
	m_iState = STATE_JUMP;
	if( fInitSpeedY == 0.0f )
		m_pArmature->playAnimation("xunhuan", true);
	else
		m_pArmature->playAnimation("qitiao", false);
	m_fCurAnimTime = 0.0f;
	m_fCurAnimTotalTime = 0.5f;
}

void SCComPlayerFSM::doAttack()
{
	if (m_iState == STATE_STAND)
		m_pArmature->playAnimation("jiguanqiang", false, false);
	else if (m_iState == STATE_MOVE)
		m_pArmature->playAnimation("benpao", false, false);
	else if (m_iState == STATE_JUMP)
		m_pArmature->playAnimation("tiaoyuekaiqiang", false, false);
	m_fCurAnimTime = 0.0f;
	m_fCurAnimTotalTime = 0.5f;
}

void SCComPlayerFSM::doDie()
{
    m_iState = STATE_DIE;
    m_pArmature->playAnimation("siwang", false, true, "siwangxunhuan");
}

void SCComPlayerFSM::update_Stand(float dt)
{
	if( m_pArmature->getCurAnimName() == "luodi" ||
		m_pArmature->getCurAnimName() == "jiguanqiang" )
	{
		m_fCurAnimTime += dt;
		if( m_fCurAnimTime >= m_fCurAnimTotalTime )
		{
			m_pArmature->playAnimation("zhanli", true);
		}
	}
	else if( m_pArmature->getCurAnimName().empty() )
	{
		m_pArmature->playAnimation("zhanli", true);
	}
}

void SCComPlayerFSM::update_Move(float dt)
{
	if (m_pArmature->getCurAnimName() == "yidonggongji")
	{
// 		m_fCurAnimTime += dt;
// 		if (m_fCurAnimTime >= m_fCurAnimTotalTime)
// 		{
// 			m_pArmature->playAnimation("benpao", true);
// 		}
		if (m_pArmature->isCurAnimComplete())
			m_pArmature->playAnimation("benpao", true);
	}

	if (m_pArmature->isCurAnimComplete())
		m_pArmature->playAnimation("benpao", true);
}

void SCComPlayerFSM::update_Jump(float dt)
{
	if( m_pArmature->getCurAnimName() == "qitiao" ||
		m_pArmature->getCurAnimName() == "tiaoyuekaiqiang" )
	{
		m_fCurAnimTime += dt;
		if( m_fCurAnimTime >= m_fCurAnimTotalTime )
			m_pArmature->playAnimation("xunhuan", true);
	}
}

void SCComPlayerFSM::update_Die(float dt)
{
}