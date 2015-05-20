/*
 * ------------------------------------------------------------------------
 *  Name:   SCGame.h
 *  Desc:   ”Œœ∑∂‘œÛ
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#ifndef __SC_GAME_H__
#define __SC_GAME_H__

#include "cocos2d.h"

class SCGame : public cocos2d::Object
{
public:
	SCGame();
	virtual ~SCGame();

	virtual bool init();
	virtual void update(float dt);

	static SCGame& getInstance();
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_GAME_H__