/*
 * ------------------------------------------------------------------------
 *  Name:   SCJoystick.h
 *  Desc:   摇杆对象
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#ifndef __SC_JOYSTICK_H__
#define __SC_JOYSTICK_H__

#include "2d/CCLayer.h"

class SCJoystick : public cocos2d::Layer
{
public:
	SCJoystick();
	virtual ~SCJoystick();

	virtual bool init();

	cocos2d::Node* getRootNode() const { return m_pRootNode; }

protected:
	cocos2d::Node* m_pRootNode;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_JOYSTICK_H__