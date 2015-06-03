/*
 * ------------------------------------------------------------------------
 *  Name:   SCComPlayerFSM.cpp
 *  Desc:   Ö÷Íæ¼Ò×´Ì¬»ú
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCComPlayerFSM.h"

SCComPlayerFSM::SCComPlayerFSM()
	: SCComponentBase(SC_COMPONENT_PLAYERFSM)
{
}

SCComPlayerFSM::~SCComPlayerFSM()
{
}

bool SCComPlayerFSM::init()
{
	m_bActive = true;
	return true;
}

void SCComPlayerFSM::update(float dt)
{
}