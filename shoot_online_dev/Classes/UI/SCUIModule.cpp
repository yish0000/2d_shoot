/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIModule.cpp
 *  Desc:   UI模块
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

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
    
    
}

void SCUIModule::clearResources()
{
}