/*
 * ------------------------------------------------------------------------
 *  Name:   SCUISkill.cpp
 *  Desc:   ���ܽ���
 *  Author: Yish
 *  Date:   2015/7/15
 * ------------------------------------------------------------------------
 */

#include "SCUISkill.h"
#include "Game/SCHostPlayer.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;
using namespace ui;

SCUISkill::SCUISkill(const std::string& name, const std::string& filename)
	: SCUIBase(name, filename)
{
}

SCUISkill::~SCUISkill()
{
}

bool SCUISkill::init()
{
	if( !SCUIBase::init() )
		return false;

	REGISTER_BUTTON_EVENT("Button_attack", SCUISkill::onBtnAttack);
	REGISTER_BUTTON_EVENT("Button_jump", SCUISkill::onBtnJump);
	return true;
}

void SCUISkill::onBtnAttack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et)
{
	if (et == Widget::TouchEventType::BEGAN)
	{
		SCHostPlayer* pHost = glb_getHostPlayer();
		pHost->GetController()->Attack();
	}
}

void SCUISkill::onBtnJump(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et)
{
	if (et == Widget::TouchEventType::BEGAN)
	{
		SCHostPlayer* pHost = glb_getHostPlayer();
		pHost->GetController()->Jump();
	}
}