/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIModule.cpp
 *  Desc:   UI模块
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "SCUIBase.h"
#include "SCUIModule.h"

SCUIModule::SCUIModule()
	: SCModuleBase(MODULE_TYPE_UI), m_fUIScale(1.0f)
{
}

SCUIModule::~SCUIModule()
{
}

bool SCUIModule::init()
{
    if( !SCModuleBase::init() )
        return false;
    
    return true;
}

void SCUIModule::update(float dt)
{
    SCModuleBase::update(dt);
    
	UITable::const_iterator it = m_UITable.begin();
	for (; it != m_UITable.end(); ++it)
	{
		SCUIBase* pFrame = it->second;
		if (pFrame->isVisible())
			pFrame->update(dt);
	}
}

void SCUIModule::clearResources()
{
}