/*
 * ------------------------------------------------------------------------
 *  Name:   SCModuleManager.cpp
 *  Desc:   Ä£¿é¹ÜÀíÆ÷
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "SCModuleManager.h"

SCModuleManager::SCModuleManager()
{
}

SCModuleManager::~SCModuleManager()
{
}

SCModuleManager& SCModuleManager::getInstance()
{
	static SCModuleManager obj;
	return obj;
}

bool SCModuleManager::init()
{
	return true;
}

void SCModuleManager::update(float dt)
{
}

SCModuleBase* SCModuleManager::getModule(int type)
{
	std::vector<SCModuleBase*>::iterator it;
	for(it=m_Modules.begin(); it!=m_Modules.end(); ++it)
	{
		if( (*it)->getModuleType() == type )
			return *it;
	}

	return NULL;
}