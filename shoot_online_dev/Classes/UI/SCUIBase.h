/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIBase.h
 *  Desc:   界面基类
 *  Author: Yish
 *  Date:   2015/6/25
 * ------------------------------------------------------------------------
 */

#ifndef __SC_UIBASE_H__
#define __SC_UIBASE_H__

#include "2d/CCNode.h"
#include "ui/CocosGUI.h"

class SCUIBase : public cocos2d::Node
{
public:
	SCUIBase();
	virtual ~SCUIBase();

	virtual bool init();
	virtual void update(float dt);

protected:
	cocos2d::ui::Widget* m_pRootWidget;		// 本界面的节点树
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UIBASE_H__