/*
 * ------------------------------------------------------------------------
 *  Name:   SCModuleManager.h
 *  Desc:   Ä£¿é¹ÜÀíÆ÷
 *  Author: Yish
 *  Date:   2015/5/22
 * ------------------------------------------------------------------------
 */

#ifndef __SC_MODULEMANAGER_H__
#define __SC_MODULEMANAGER_H__

#include <vector>
#include "SCModuleBase.h"

class SCModuleManager : public SCEventDispatcher
{
public:
	typedef std::vector<SCModuleBase*> ModuleList;

public:
	SCModuleManager();
	virtual ~SCModuleManager();

	bool init();
	void update(float dt);

	SCModuleBase* getModule(int ID);

protected:
	ModuleList m_Modules;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_MODULEMANAGER_H__