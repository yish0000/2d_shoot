/*
 * ------------------------------------------------------------------------
 *  Name:   SCGameJoystick.cpp
 *  Desc:   游戏手柄对象
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCGameJoystick.h"
#include "Player/SCHostPlayer.h"
#include "Utility/SCUtilityFunc.h"

static const char* JOYSTICK_BACK = "ui/joystick/back.png";
static const char* JOYSTICK_CENTER = "ui/joystick/center.png";

SCGameJoystick::SCGameJoystick()
	: SCJoystickBase(JOYSTICK_BACK, JOYSTICK_CENTER)
{
}

// 这里处理游戏手柄逻辑
void SCGameJoystick::onJoystickHandle(float xDir, float yDir)
{
	SCHostPlayer* pHost = glb_getHostPlayer();
	pHost->move(xDir, yDir);
	CCLOG("onJoystickHandle, x=%f, y=%f", xDir, yDir);
}