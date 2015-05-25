/*
 * ------------------------------------------------------------------------
 *  Name:   SCWorld.cpp
 *  Desc:   世界对象
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "SCWorld.h"

SCWorld::SCWorld()
{
}

SCWorld::~SCWorld()
{
}

bool SCWorld::init()
{
	if( !Node::init() )
		return false;

	return true;
}

void SCWorld::update(float dt)
{
}