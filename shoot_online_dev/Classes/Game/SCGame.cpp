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
#include "Utility/SCUtilityFunc.h"
#include "Player/SCPlayerModule.h"
#include "Player/SCHostPlayer.h"
#include <Game/SCWorld.h>

USING_NS_CC;

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

	// 更新世界
	m_pWorld->update(dt);
}

// 临时代码， DEMO
void SCGame::changeGameState(SCGame::GAMESTATE state)
{
	SCSceneManager::getInstance().enterScene(SCENE_BATTLE, TRANS_FADEIN, 0.4f);

	SCSceneBase* pCurScene = SCSceneManager::getInstance().getCurScene();
	m_pWorld = SCWorld::create();
	pCurScene->addChild(m_pWorld);

	// 加载主玩家
	SCHostPlayer* pHost = glb_getPlayerModule()->getHostPlayer();
	m_pWorld->getTileMap()->addChildToLayer(pHost, "rd_add", SCENELAYER_ZORDER_HOSTPLAYER);
	pHost->setPosition(300, 120);
	pHost->setScale(0.7f);

	// 地图跟随主角
	m_pWorld->getTileMap()->followNode(pHost);
}