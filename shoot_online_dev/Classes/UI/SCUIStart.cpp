/*
* ------------------------------------------------------------------------
*  Name:   SCUIStart.cpp
*  Desc:   游戏开始界面
*  Author: Yish
*  Date:   2015/8/20
* ------------------------------------------------------------------------
*/

#include "SCUIStart.h"
#include "Main/SCGame.h"

USING_NS_CC;
using namespace ui;

SCUIStart::SCUIStart(const std::string& name, const std::string& filename)
	: SCUIBase(name, filename)
{
}

SCUIStart::~SCUIStart()
{
}

bool SCUIStart::init()
{
	if (!SCUIBase::init())
		return false;

	REGISTER_BUTTON_EVENT("Button_start", SCUIStart::onBtnStart);
	REGISTER_BUTTON_EVENT("Button_option", SCUIStart::onBtnSettings);
	return true;
}

void SCUIStart::onBtnStart(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et)
{
	if (et == Widget::TouchEventType::ENDED)
		SCGame::getInstance().changeGameState(SCGame::GS_MAIN);
}

void SCUIStart::onBtnSettings(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et)
{
	if (et == Widget::TouchEventType::ENDED)
	{
		SCUIBase* pFrame = getUIFrame("Option");
		if (pFrame)
		{
			pFrame->showUI();

			int* p = NULL;
			*p = 0;
		}
	}
}