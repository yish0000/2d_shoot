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

void SCModuleBase::onEventModuleInited(SCEvent* pEvent)
{
}

void SCModuleBase::clearResources()
{
}