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
#include "Player/SCPlayerModule.h"
#include "Game/SCGameModule.h"
#include "Game/SCWorld.h"
#include "SCGame.h"

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
	return glb_getWorld()->getHostPlayer();
}

SCWorld* glb_getWorld()
{
	return glb_getGameModule()->getWorld();
}

SCTiledMap* glb_getTiledMap()
{
	return glb_getWorld()->getTileMap();
}