/*
 * ------------------------------------------------------------------------
 *  Name:   SCComNPCFSM.cpp
 *  Desc:   NPC×´Ì¬»ú
 *  Author: Yish
 *  Date:   2015/8/3
 * ------------------------------------------------------------------------
 */

#include "SCComNPCFSM.h"

SCComNPCFSM::SCComNPCFSM()
	: SCComponentBase(SC_COMPONENT_NPCFSM)
{
	m_iState = STATE_STAND;
}

SCComNPCFSM::~SCComNPCFSM()
{
}

bool SCComNPCFSM::init()
{
	m_bActive = true;
	return true;
}

void SCComNPCFSM::update(float dt)
{
}

void SCComNPCFSM::doStand(bool afterJump /* = false */)
{
	m_iState = STATE_STAND;
}

void SCComNPCFSM::doRun()
{
	m_iState = STATE_MOVE;
}

void SCComNPCFSM::doJump(float fInitSpeedY)
{
	m_iState = STATE_JUMP;
}

void SCComNPCFSM::doAttack()
{
}