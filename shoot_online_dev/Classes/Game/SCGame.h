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

class SCTiledMap;

class SCGame : public cocos2d::Ref
{
public:

	enum GAMESTATE
	{
		GS_NONE,
		GS_LOADING,     // 加载
        GS_LOGIN,       // 登陆
		GS_MAIN,        // 游戏主界面
		GS_BATTLE,      // 关卡
	};

public:
	SCGame();
	virtual ~SCGame();

	virtual void start();
	virtual void update(float dt);
    
    // 从本地加载数据
    bool loadData();
    // 保存数据到本地
    void saveData();
    
    // 改变游戏状态
    void changeGameState(GAMESTATE state);

	GAMESTATE getGameState() const { return m_gameState; }

	static SCGame& getInstance();

protected:
	GAMESTATE m_gameState;
	SCTiledMap* m_pMap;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_GAME_H__