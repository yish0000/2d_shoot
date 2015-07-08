/*
 * ------------------------------------------------------------------------
 *  Name:   SCGameJoystick.cpp
 *  Desc:   ��Ϸ�ֱ�����
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
{
}

// ���ﴦ����Ϸ�ֱ��߼�
void SCGameJoystick::onJoystickHandle(float xDir, float yDir)
{
	SCHostPlayer* pHost = glb_getHostPlayer();
	pHost->GetController()->Move(xDir, yDir);
}