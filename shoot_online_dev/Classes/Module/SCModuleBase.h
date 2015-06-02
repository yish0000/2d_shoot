/*
 * ------------------------------------------------------------------------
 *  Name:   SCModuleBase.h
 *  Desc:   模块基类
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#ifndef __SC_MODULEBASE_H__
#define __SC_MODULEBASE_H__

#include "Common/SCEvent.h"
#include "Common/SCEventTypes.h"
#include "SCModuleTypes.h"

class SCModuleBase : public SCEventListener
{
public:
	SCModuleBase();
	virtual ~SCModuleBase();

	virtual bool init();
	virtual void update(float dt);

	// 清理资源
	virtual void clearResources();

	// 注册事件
	void addEventListener(const std::string& eventType, SEL_SCEventCallback callback, int priority=0);

	// 派发事件
	void dispatchEvent(SCEvent* pEvent);
	void dispatchEvent(const std::string& eventName);

	// 获取模块类型
	int getModuleType() const { return m_iType; }

protected:
	int m_iType;	// 模块类型

	virtual void onEventModuleInited(SCEvent* pEvent);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_MODULEBASE_H__