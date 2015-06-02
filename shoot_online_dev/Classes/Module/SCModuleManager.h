/*
 * ------------------------------------------------------------------------
 *  Name:   SCModuleManager.h
 *  Desc:   模块管理器
 *  Author: Yish
 *  Date:   2015/5/22
 * ------------------------------------------------------------------------
 */

#ifndef __SC_MODULEMANAGER_H__
#define __SC_MODULEMANAGER_H__

#include <map>
#include "SCModuleBase.h"

class SCModuleManager : public SCEventDispatcher
{
public:
	typedef std::map<int, SCModuleBase*> ModuleMap;

public:
	SCModuleManager();
	virtual ~SCModuleManager();

	bool init();
	void update(float dt);
	void clearResources();

	SCModuleBase* getModule(int type);

	static SCModuleManager& getInstance();

protected:
	ModuleMap m_Modules;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_MODULEMANAGER_H__