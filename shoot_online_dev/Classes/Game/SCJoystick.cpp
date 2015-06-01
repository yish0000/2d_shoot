/*
 * ------------------------------------------------------------------------
 *  Name:   SCJoystick.cpp
 *  Desc:   手柄对象
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "SCJoystick.h"

SCJoystick::SCJoystick(const std::string& back_img, const std::string& center_img)
	: m_sJoystickBack(back_img), m_sJoystickCenter(center_img), m_pSpriteBack(NULL), m_pSpriteCenter(NULL)
	, m_fX(0.0f), m_fY(0.0f), m_fPosX(0.0f), m_fPosY(0.0f)
{
}

SCJoystick::~SCJoystick()
{
}

bool SCJoystick::init()
{
	if( !Node::init() )
		return false;

	// WINDOWS平台注册
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	setAccelerometerEnabled(true);
#endif

	return true;
}