/*
 * ------------------------------------------------------------------------
 *  Name:   UIModule.cpp
 *  Desc:   UI模块
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "UIModule.h"

UIModule::UIModule()
	: SCModuleBase(MODULE_TYPE_UI), m_fUIScale(1.0f)
{
}

UIModule::~UIModule()
{
}

bool UIModule::init()
{
    if( !SCModuleBase::init() )
        return false;
    
    return true;
}

void UIModule::update(float dt)
{
    SCModuleBase::update(dt);
    
    
}

void UIModule::clearResources()
{
}