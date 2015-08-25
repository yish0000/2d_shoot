/*
 * ------------------------------------------------------------------------
 *  Name:   SCGameJoystick.cpp
 *  Desc:   游戏手柄对象
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCGameJoystick.h"
#include "SCHostPlayer.h"
#include "Utility/SCUtilityFunc.h"

static const char* JOYSTICK_BACK = "ui/joystick/back.png";
static const char* JOYSTICK_CENTER = "ui/joystick/center.png";

SCGameJoystick::SCGameJoystick()
	: SCJoystickBase(JOYSTICK_BACK, JOYSTICK_CENTER), m_pController(NULL)
	, m_fXDir(0.0f), m_fYDir(0.0f)
{
}

// 这里处理游戏手柄逻辑
void SCGameJoystick::onJoystickHandle(float xDir, float yDir)
{
	m_fXDir = xDir;
	m_fYDir = yDir;

	SCHostPlayer* pHost = glb_getHostPlayer();
	pHost->GetController()->Move(xDir, yDir);
}