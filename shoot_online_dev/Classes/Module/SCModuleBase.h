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

	int getModuleType() const { return m_iType; }
	float getUpdateInterval() const { return m_fUpdateInterval; }

	// 注册事件
	void addEventListener(const std::string& eventType, SEL_SCEventCallback callback, int priority=0);

	// 派发事件
	void dispatchEvent(SCEvent* pEvent);
	void dispatchEvent(const std::string& eventName);

protected:
	int m_iType;
	float m_fUpdateInterval;

	virtual void onEventModuleInited(SCEvent* pEvent);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_MODULEBASE_H__