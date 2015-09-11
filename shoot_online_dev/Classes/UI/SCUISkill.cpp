/*
 * ------------------------------------------------------------------------
 *  Name:   SCUISkill.cpp
 *  Desc:   技能界面
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
	: SCUIBase(name, filename), m_pPrgHP(NULL), m_pPrgMP(NULL)
{
}

SCUISkill::~SCUISkill()
{
}

bool SCUISkill::init()
{
	if( !SCUIBase::init() )
		return false;

	DDX_Control(m_pPrgHP, "Image_playerbg/ProgressBar_hp");
	DDX_Control(m_pPrgMP, "Image_playerbg/ProgressBar_mp");

	REGISTER_BUTTON_EVENT("Button_attack", SCUISkill::onBtnAttack);
	REGISTER_BUTTON_EVENT("Button_jump", SCUISkill::onBtnJump);
	return true;
}

void SCUISkill::update(float dt)
{
	SCUIBase::update(dt);

	int curHP = glb_getHostPlayer()->getCurHP();
	int maxHP = glb_getHostPlayer()->getMaxHP();
	int curProg = (int)((float)curHP / maxHP * 100);
	if (curProg != (int)m_pPrgHP->getPercent())
	{
		m_pPrgHP->setPercent(curProg);
	}
}

void SCUISkill::onBtnAttack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et)
{
	SCHostPlayer* pHost = glb_getHostPlayer();

	if (et == Widget::TouchEventType::BEGAN)
	{
		pHost->GetController()->AttackBegin();
	}
	else if (et == Widget::TouchEventType::ENDED || et == Widget::TouchEventType::CANCELED)
	{
		pHost->GetController()->AttackEnd();
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