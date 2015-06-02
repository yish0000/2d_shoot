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

bool SCGame::init()
{
	// 初始化各个模块
	SCModuleManager::getInstance().init();

	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
	return true;
}

void SCGame::update(float dt)
{
	// 更新各个模块
	SCModuleManager::getInstance().update(dt);


}

