/*
 * ------------------------------------------------------------------------
 *  Name:   SCUISkill.cpp
 *  Desc:   技能界面
 *  Author: Yish
 *  Date:   2015/7/15
 * ------------------------------------------------------------------------
 */

#include "SCUISkill.h"

USING_NS_CC;

SCUISkill::SCUISkill(const std::string& filename)
	: SCUIBase(filename)
{
}

SCUISkill::~SCUISkill()
{
}

bool SCUISkill::init()
{
	if( !SCUIBase::init() )
		return false;

	return true;
}

void SCUISkill::onBtnAttack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et)
{
}

void SCUISkill::onBtnJump(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et)
{
}