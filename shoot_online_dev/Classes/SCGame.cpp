/*
 * ------------------------------------------------------------------------
 *  Name:   SCGame.cpp
 *  Desc:   游戏对象
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#include "SCGame.h"
#include "Module/SCModuleManager.h"
#include "Utility/SCConfigs.h"

USING_NS_CC;

///////////////////////////////////////////////////////////////////////////

static const char* APP_CONFIG_FILE = "config/app_config.json";

///////////////////////////////////////////////////////////////////////////

SCGame& SCGame::getInstance()
{
	static SCGame obj;
	return obj;
}

SCGame::SCGame()
{
	m_gameState = GS_NONE;
	m_pWorld = NULL;
}

SCGame::~SCGame()
{
}

void SCGame::start()
{
	int * p = NULL;
	*p = 5;
	// 加载全局配置信息
	SCConfigs::getInstance().load(APP_CONFIG_FILE);

    // 注册游戏心跳函数
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
	
    // 初始化各个模块
	SCModuleManager::getInstance().init();

    // 进入游戏场景（DEMO）
    changeGameState(GS_BATTLE);
}

void SCGame::update(float dt)
{
	// 更新各个模块
	SCModuleManager::getInstance().update(dt);

}

void SCGame::onEnterForeground()
{
	SCModuleManager::getInstance().dispatchEvent(SC_EVENT_APP_ENTERFRONT);
}

void SCGame::onEnterBackground()
{
	SCModuleManager::getInstance().dispatchEvent(SC_EVENT_APP_ENTERBACK);
}

// 临时代码， DEMO
void SCGame::changeGameState(SCGame::GAMESTATE state)
{

}