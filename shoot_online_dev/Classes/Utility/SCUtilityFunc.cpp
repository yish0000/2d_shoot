/*
 * ------------------------------------------------------------------------
 *  Name:   SCUtilityFunc.cpp
 *  Desc:   һЩʵ�ú���
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