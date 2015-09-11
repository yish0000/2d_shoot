/*
 * ------------------------------------------------------------------------
 *  Name:   SCUISkill.h
 *  Desc:   技能界面
 *  Author: Yish
 *  Date:   2015/7/15
 * ------------------------------------------------------------------------
 */

#ifndef __SC_UISKILL_H__
#define __SC_UISKILL_H__

#include "SCUIBase.h"

class SCUISkill : public SCUIBase
{
public:
	SCUISkill(const std::string& name, const std::string& filename);
	virtual ~SCUISkill();

	virtual bool init();
	virtual void update(float dt);

protected:
	cocos2d::ui::LoadingBar* m_pPrgHP;
	cocos2d::ui::LoadingBar* m_pPrgMP;
	
protected:
	void onBtnAttack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et);
	void onBtnJump(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UISKILL_H__