/*
 * ------------------------------------------------------------------------
 *  Name:   SCGameJoystick.h
 *  Desc:   ��Ϸ�ֱ�����
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_GAMEJOYSTICK_H__
#define __SC_GAMEJOYSTICK_H__

#include "Utility/SCJoystickBase.h"

class SCHostPlayerController;

class SCGameJoystick : public SCJoystickBase
{
public:
	SCGameJoystick();
	CREATE_FUNC(SCGameJoystick);

	// ҡ�˴�����
	virtual void onJoystickHandle(float xDir, float yDir);

	void setHostPlayerController(SCHostPlayerController* pController) { m_pController = pController; }

	float getXDir() const { return m_fXDir; }
	float getYDir() const { return m_fYDir; }

protected:
    SCHostPlayerController *m_pController;
	float m_fXDir, m_fYDir;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_GAMEJOYSTICK_H__