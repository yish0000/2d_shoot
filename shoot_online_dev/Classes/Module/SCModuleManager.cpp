﻿/*
 * ------------------------------------------------------------------------
 *  Name:   SCModuleManager.cpp
 *  Desc:   模块管理器
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "cocos2d.h"
#include "SCModuleManager.h"

#include "Network/SCNetworkModule.h"
#include "UI/UIModule.h"

USING_NS_CC;

///////////////////////////////////////////////////////////////////////////

#define REGISTER_MODULE(id, module) \
	{\
		if( m_Modules.find(id) != m_Modules.end() ) \
			CCASSERT(0, "Module register duplicated!!"); \
		module* pModule = new module(); \
		m_Modules[id] = pModule; \
	}

///////////////////////////////////////////////////////////////////////////

SCModuleManager::SCModuleManager()
{
}

SCModuleManager::~SCModuleManager()
{
	ModuleMap::iterator it = m_Modules.begin();
	while( it != m_Modules.end() )
	{
		delete it->second;
		++it;
	}
}

SCModuleManager& SCModuleManager::getInstance()
{
	static SCModuleManager obj;
	return obj;
}

bool SCModuleManager::init()
{
	REGISTER_MODULE(MODULE_TYPE_NETWORK, SCNetworkModule);
	REGISTER_MODULE(MODULE_TYPE_UI, UIModule);

	for(ModuleMap::iterator it=m_Modules.begin(); it!=m_Modules.end(); ++it)
	{
		if( !it->second->init() )
		{
			CCLOG("SCModuleManager::init, Module (%d) initialized failed!", it->second->getModuleType());
			return false;
		}
	}

	return true;
}

void SCModuleManager::update(float dt)
{
	ModuleMap::iterator it = m_Modules.begin();
	for(; it!=m_Modules.end(); ++it)
	{
		it->second->update(dt);
	}
}

SCModuleBase* SCModuleManager::getModule(int type)
{
	ModuleMap::iterator it = m_Modules.find(type);
	return it != m_Modules.end() ? it->second : NULL;
}

void SCModuleManager::clearResources()
{
	ModuleMap::iterator it = m_Modules.begin();
	for(; it!=m_Modules.end(); ++it)
	{
		it->second->clearResources();
	}
}