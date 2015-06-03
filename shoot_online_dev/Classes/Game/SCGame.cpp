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
#include "Scene/SCTiledMap.h"
#include "cocos2d.h"

USING_NS_CC;

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

// 临时代码， DEMO
void SCGame::changeGameState(SCGame::GAMESTATE state)
{
	SCSceneManager::getInstance().enterScene(SCENE_BATTLE, TRANS_FADEIN, 0.4f);

	SCSceneBase* pCurScene = SCSceneManager::getInstance().getCurScene();
	SCTiledMap* pMap = SCTiledMap::create(0);
	pCurScene->addChild(pMap);
}