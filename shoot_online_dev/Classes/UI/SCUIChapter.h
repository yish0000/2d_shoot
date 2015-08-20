/*
* ------------------------------------------------------------------------
*  Name:   SCUIChapter.h
*  Desc:   游戏开始界面
*  Author: Yish
*  Date:   2015/8/20
* ------------------------------------------------------------------------
*/

#ifndef __SC_UICHAPTER_H__
#define __SC_UICHAPTER_H__

#include "SCUIBase.h"

class SCUIChapter : public SCUIBase
{
public:
	SCUIChapter(const std::string& name, const std::string& filename);
	virtual ~SCUIChapter();

	virtual bool init();

	void onBtnChapter(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et);
	void onBtnReturn(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType et);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UICHAPTER_H__