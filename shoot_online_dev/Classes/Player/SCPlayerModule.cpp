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
    : SCModuleBase(MODULE_TYPE_PLAYER), m_pHostPlayer(NULL)
{
}

SCPlayerModule::~SCPlayerModule()
{
	CC_SAFE_DELETE(m_pHostPlayer);
}

bool SCPlayerModule::init()
{
    if( !SCModuleBase::init() )
        return false;

	// 注册函数处理
	REGISTER_PROTO_HANDLER(555, SCPlayerModule::onPrtcUserInfo);
    
	m_pHostPlayer = new SCHostPlayer();
	m_pHostPlayer->init();
    return true;
}

void SCPlayerModule::onPrtcUserInfo(const scnet::Protocol* p)
{
}

void SCPlayerModule::update(float dt)
{
    SCModuleBase::update(dt);
    
    m_pHostPlayer->update(dt);
}

void SCPlayerModule::clearResources()
{
}