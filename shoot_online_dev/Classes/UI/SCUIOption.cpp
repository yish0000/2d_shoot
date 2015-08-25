/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIOption.cpp
 *  Desc:   配置选项界面
 *  Author: Yish
 *  Date:   2015/8/20
 * ------------------------------------------------------------------------
 */

#include "SCUIOption.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace ui;

SCUIOption::SCUIOption(const std::string& name, const std::string& filename)
	: SCUIBase(name, filename)
{
}

SCUIOption::~SCUIOption()
{
}

bool SCUIOption::init()
{
	if (!SCUIBase::init())
		return false;
	m_pRootWidget->addTouchEventListener(std::bind([&] {
		hideUI();
	}));

	return true;
}