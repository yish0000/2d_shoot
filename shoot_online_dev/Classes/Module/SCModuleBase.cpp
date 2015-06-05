/*
 * ------------------------------------------------------------------------
 *  Name:   SCModuleBase.cpp
 *  Desc:   模块基类
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#include "SCModuleBase.h"
#include "SCModuleManager.h"
#include "Network/netlib/protocol/Protocol.h"
#include "cocos2d.h"

USING_NS_CC;

SCModuleBase::SCModuleBase(int type) : m_iType(type)
{
}

SCModuleBase::~SCModuleBase()
{
}

bool SCModuleBase::init()
{
	addEventListener(SC_EVENT_MODULE_INITED, sceventcallback_selector(SCModuleBase::onEventModuleInited));
	addEventListener(SC_EVENT_NEW_PROTOCOL, sceventcallback_selector(SCModuleBase::onEventNewProtocol));
	return true;
}

void SCModuleBase::addEventListener(const std::string& eventType, SEL_SCEventCallback callback, int priority/* =0 */)
{
	SCModuleManager::getInstance().addEventListener(eventType, this, callback, priority);
}

void SCModuleBase::dispatchEvent(SCEvent* pEvent)
{
	SCModuleManager::getInstance().dispatchEvent(pEvent);
}

void SCModuleBase::dispatchEvent(const std::string& eventName)
{
	SCModuleManager::getInstance().dispatchEvent(eventName);
}

void SCModuleBase::update(float dt)
{
}

void SCModuleBase::registerProtoHandler(int protoType, const ProtocolHandler& handler)
{
	if( m_protoHandlers.find(protoType) != m_protoHandlers.end() )
	{
		CCLOG("SCModuleBase::registerProtoHandler, protocol handler (%d) duplicated!!", protoType);
		return;
	}

	m_protoHandlers[protoType] = handler;
}

void SCModuleBase::onEventModuleInited(SCEvent* pEvent)
{
	CCLOG("SCModuleBase::onEventModuleInited %d", m_iType);
}

void SCModuleBase::onEventNewProtocol(SCEvent* pEvent)
{
	SCEventNewProtocol* pEventNew = dynamic_cast<SCEventNewProtocol*>(pEvent);
	const scnet::Protocol* newProto = pEventNew->getProtocol();

	ProtocolHandlerMap::iterator it = m_protoHandlers.find(newProto->type);
	if( it != m_protoHandlers.end() )
	{
		it->second(newProto);
	}
}

void SCModuleBase::clearResources()
{
}