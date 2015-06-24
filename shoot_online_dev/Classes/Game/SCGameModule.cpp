/*
 * ------------------------------------------------------------------------
 *  Name:   SCGameModule.cpp
 *  Desc:   游戏逻辑模块
 *  Author: Yish
 *  Date:   2015/6/24
 * ------------------------------------------------------------------------
 */

#include "SCGameModule.h"
#include "Scene/SCSceneManager.h"
#include "Scene/SCSceneBase.h"
#include "SCHostPlayer.h"
#include "Utility/SCUtilityFunc.h"

SCGameModule::SCGameModule()
	: SCModuleBase(MODULE_TYPE_GAME), m_pWorld(NULL)
{
}

SCGameModule::~SCGameModule()
{
}

bool SCGameModule::init()
{
	if (!SCModuleBase::init())
		return false;

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
	return true;
}

void SCGameModule::update(float dt)
{
	SCModuleBase::update(dt);

	if (m_pWorld)
		m_pWorld->update(dt);
}