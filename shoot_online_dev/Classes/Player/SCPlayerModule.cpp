/*
 * ------------------------------------------------------------------------
 *  Name:   SCPlayerModule.cpp
 *  Desc:   主玩家模块
 *  Author: Yish
 *  Date:   2015/6/2
 * ------------------------------------------------------------------------
 */

#include "SCPlayerModule.h"

SCPlayerModule::SCPlayerModule()
    : SCModuleBase(MODULE_TYPE_PLAYER)
{
}

SCPlayerModule::~SCPlayerModule()
{
}

bool SCPlayerModule::init()
{
    if( !SCModuleBase::init() )
        return false;

	// 注册函数处理
	REGISTER_PROTO_HANDLER(555, SCPlayerModule::onPrtcUserInfo);
    
    return true;
}

void SCPlayerModule::onPrtcUserInfo(const scnet::Protocol* p)
{
}

void SCPlayerModule::update(float dt)
{
    SCModuleBase::update(dt);
    
}

void SCPlayerModule::clearResources()
{
}