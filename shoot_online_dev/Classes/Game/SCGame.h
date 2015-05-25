/*
 * ------------------------------------------------------------------------
 *  Name:   SCGame.h
 *  Desc:   游戏对象
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#ifndef __SC_GAME_H__
#define __SC_GAME_H__

#include "cocos2d.h"

class SCGame : public cocos2d::Ref
{
public:

	enum GAMESTATE
	{
		GS_NONE,
		GS_LOADING,
		GS_MAIN,
		GS_BATTLE,
	};

public:
	SCGame();
	virtual ~SCGame();

	virtual bool init();
	virtual void update(float dt);

	GAMESTATE getGameState() const { return m_gameState; }

	static SCGame& getInstance();

protected:
	GAMESTATE m_gameState;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_GAME_H__