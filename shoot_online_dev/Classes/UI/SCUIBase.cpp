/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIBase.cpp
 *  Desc:   界面基类
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