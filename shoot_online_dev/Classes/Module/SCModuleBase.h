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

#define REGISTER_PROTO_HANDLER(type, func) \
	registerProtoHandler(type, CC_CALLBACK_1(func, this))

class SCModuleBase : public SCEventListener
{
	typedef std::function<void(const scnet::Protocol*)> ProtocolHandler;
	typedef std::map<int, ProtocolHandler> ProtocolHandlerMap;

public:
	SCModuleBase(int type);
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
	ProtocolHandlerMap m_protoHandlers;

protected:
	void registerProtoHandler(int protoType, const ProtocolHandler& handler);

	// Event Handlers.
	virtual void onEventModuleInited(SCEvent* pEvent);
	virtual void onEventNewProtocol(SCEvent* pEvent);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_MODULEBASE_H__