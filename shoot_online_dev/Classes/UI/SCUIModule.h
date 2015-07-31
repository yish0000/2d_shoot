﻿/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIModule.h
 *  Desc:   UI模块
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#ifndef __SC_UIMODULE_H__
#define __SC_UIMODULE_H__

#include <unordered_map>
#include <2d/CCLayer.h>
#include "Module/SCModuleBase.h"
#include "SCUITypes.h"

class SCUIBase;

/** UI模块
*/
class SCUIModule : public SCModuleBase
{
public:

	struct UIMetaInfo
	{
		std::string name;			// 界面名称
		std::string filename;		// 界面文件
		UIFrameType type;			// 界面类型
		bool visible;				// 初始时是否显示
		std::string parent_name;	// 父界面
		int zOrder;					// z值
		bool modalDlg;				// 是否是模态对话框

		UIMetaInfo() : type(FRAME_COMMON), visible(false), zOrder(0), modalDlg(false) {}
	};

	typedef std::unordered_map<std::string, UIMetaInfo> UIMetaInfoTable;
	typedef std::unordered_map<std::string, SCUIBase*> UITable;

public:
	SCUIModule();
	virtual ~SCUIModule();
    
    virtual bool init();
    virtual void update(float dt);
    
    virtual void clearResources();

	// 切换界面类型
	void changeUIType(UIFrameType type);

	// 获取指定的界面
	SCUIBase* getUIFrame(const std::string& name);

	float getUIScale() const { return m_fUIScale; }

	// 获取UI层
	cocos2d::Layer* getUILayer();
	
protected:
	UIFrameType m_iCurType;
	float m_fUIScale;
	UIMetaInfoTable m_UIMetas;
	UITable m_UITable;

	bool loadUIMetaData();
	void initUICreateFunc();
	SCUIBase* createUIFrame(const std::string& name);

protected:	// Event handlers.
	void onEventModuleInited(SCEvent* pEvent);
	
protected:	// Protocol handlers.
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UIMODULE_H__