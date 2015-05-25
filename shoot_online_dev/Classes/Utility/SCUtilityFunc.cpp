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

int glb_getGameState()
{
	return SCGame::getInstance().getGameState();
}

SCModuleBase* glb_getModule(int moduleType)
{
	return SCModuleManager::getInstance().getModule(moduleType);
}