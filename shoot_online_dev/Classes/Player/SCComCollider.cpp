/*
 * ------------------------------------------------------------------------
 *  Name:   SCComCollider.cpp
 *  Desc:   Åö×²¼ì²â×é¼þ
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCComCollider.h"

SCComCollider::SCComCollider()
	: SCComponentBase(SC_COMPONENT_COLLIDER)
{
}

SCComCollider::~SCComCollider()
{
}

bool SCComCollider::init()
{
	m_bActive = true;
	return true;
}

void SCComCollider::update(float dt)
{
}