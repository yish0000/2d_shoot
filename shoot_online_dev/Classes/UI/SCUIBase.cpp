/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIBase.cpp
 *  Desc:   �������
 *  Author: Yish
 *  Date:   2015/6/25
 * ------------------------------------------------------------------------
 */

#include "SCUIBase.h"

SCUIBase::SCUIBase()
{
}

SCUIBase::~SCUIBase()
{
}

bool SCUIBase::init()
{
	if (!Node::init())
		return false;


	return true;
}

void SCUIBase::update(float dt)
{
	Node::update(dt);

}