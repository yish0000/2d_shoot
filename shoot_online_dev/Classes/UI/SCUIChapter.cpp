/*
* ------------------------------------------------------------------------
*  Name:   SCUIChapter.cpp
*  Desc:   游戏开始界面
*  Author: Yish
*  Date:   2015/8/20
* ------------------------------------------------------------------------
*/

#include "SCUIChapter.h"
#include "Main/SCGame.h"

USING_NS_CC;
using namespace ui;

SCUIChapter::SCUIChapter(const std::string& name, const std::string& filename)
	: SCUIBase(name, filename)
{
}

SCUIChapter::~SCUIChapter()
{
}

bool SCUIChapter::init()
{
	if (!SCUIBase::init())
		return false;

	REGISTER_BUTTON_EVENT("Button_chapter0", SCUIChapter::onBtnChapter);
	REGISTER_BUTTON_EVENT("Button_back", SCUIChapter::onBtnReturn);
	return true;
}

void SCUIChapter::onBtnChapter(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et)
{
	if (et == Widget::TouchEventType::ENDED)
		SCGame::getInstance().changeGameState(SCGame::GS_BATTLE);
}

void SCUIChapter::onBtnReturn(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et)
{
	if (et == Widget::TouchEventType::ENDED)
		SCGame::getInstance().changeGameState(SCGame::GS_LOGIN);
}