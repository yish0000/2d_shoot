/*
 * ------------------------------------------------------------------------
 *  Name:   SCJoystick.cpp
 *  Desc:   手柄对象
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "SCJoystick.h"

SCJoystick::SCJoystick()
{
}

SCJoystick::~SCJoystick()
{
}

bool SCJoystick::init()
{
	if( !Node::init() )
		return false;

	return true;
}