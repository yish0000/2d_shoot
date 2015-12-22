/*
* ------------------------------------------------------------------------
*  Name:   SCUICustom.cpp
*  Desc:   游戏开始界面
*  Author: Yish
*  Date:   2015/8/20
* ------------------------------------------------------------------------
*/

#include "SCUICustom.h"

SCUICustom::SCUICustom(const std::string& name, const std::string& filename)
	: SCUIBase(name, filename)
{
}

SCUICustom::~SCUICustom()
{
}

bool SCUICustom::init()
{
	if (!SCUIBase::init())
		return false;

	m_pRootWidget->addTouchEventListener(std::bind([&] {
		hideUI();
	}));

	return true;
}