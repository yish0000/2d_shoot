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
#include "Scene/SCSceneManager.h"
#include "Utility/SCConfigs.h"
#include "cocos2d.h"

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
}

SCGame::~SCGame()
{
}

void SCGame::start()
{
	// 加载全局配置信息
	SCConfigs::getInstance().load(APP_CONFIG_FILE);

    // 注册游戏心跳函数
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
	
    // 初始化各个模块
	SCModuleManager::getInstance().init();

    // 进入游戏登陆状态
    changeGameState(GS_LOGIN);
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

// 切换游戏状态
void SCGame::changeGameState(SCGame::GAMESTATE state)
{
	GAMESTATE oldState = m_gameState;
	m_gameState = state;

	switch (m_gameState)
	{
	case GS_LOGIN:
		SCSceneManager::getInstance().enterScene(SCENE_LOGIN, TRANS_FADEIN, 0.5f);
		break;
	case GS_MAIN:
		SCSceneManager::getInstance().enterScene(SCENE_MAIN, TRANS_FADEIN, 0.5f);
		break;
	case GS_BATTLE:
		SCSceneManager::getInstance().enterScene(SCENE_BATTLE, TRANS_FADEIN, 0.5f);
		break;
	}

	SCModuleManager::getInstance().dispatchEvent(new SCEventSwitchGameState((int)oldState, (int)state));
}