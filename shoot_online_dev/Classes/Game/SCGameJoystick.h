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

    virtual bool init();
	// ҡ�˴�����
	virtual void onJoystickHandle(float xDir, float yDir);
protected:
    SCHostPlayerController *pController;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_GAMEJOYSTICK_H__