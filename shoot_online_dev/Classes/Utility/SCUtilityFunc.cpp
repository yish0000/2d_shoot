/*
 * ------------------------------------------------------------------------
 *  Name:   SCUtilityFunc.cpp
 *  Desc:   一些实用函数
 *  Author: Yish
 *  Date:   2015/5/22
 * ------------------------------------------------------------------------
 */

#include "SCUtilityFunc.h"
#include "Module/SCModuleManager.h"
#include "Game/SCGame.h"
#include "Player/SCPlayerModule.h"
#include "Scene/SCWorld.h"

int glb_getGameState()
{
	return SCGame::getInstance().getGameState();
}

SCModuleBase* glb_getModule(int moduleType)
{
	return SCModuleManager::getInstance().getModule(moduleType);
}

SCHostPlayer* glb_getHostPlayer()
{
	return glb_getPlayerModule()->getHostPlayer();
}

SCWorld* glb_getWorld()
{
	return SCGame::getInstance().getWorld();
}

SCTiledMap* glb_getTiledMap()
{
	return glb_getWorld()->getTileMap();
}