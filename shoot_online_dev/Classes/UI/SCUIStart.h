/*
* ------------------------------------------------------------------------
*  Name:   SCUIStart.h
*  Desc:   游戏开始界面
*  Author: Yish
*  Date:   2015/8/20
* ------------------------------------------------------------------------
*/

#ifndef __SC_UISTART_H__
#define __SC_UISTART_H__

#include "SCUIBase.h"

class SCUIStart : public SCUIBase
{
public:
	SCUIStart(const std::string& name, const std::string& filename);
	virtual ~SCUIStart();

	virtual bool init();

	void onBtnStart(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et);
	void onBtnSettings(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et);

protected:
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UISTART_H__