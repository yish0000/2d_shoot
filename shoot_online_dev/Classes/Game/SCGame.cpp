/*
 * ------------------------------------------------------------------------
 *  Name:   SCGame.cpp
 *  Desc:   ��Ϸ����
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#include "SCGame.h"

SCGame& SCGame::getInstance()
{
	static SCGame obj;
	return obj;
}

SCGame::SCGame()
{

}

SCGame::~SCGame()
{
}

bool SCGame::init()
{
	return true;
}

void SCGame::update(float dt)
{
}

