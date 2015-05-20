/*
 * ------------------------------------------------------------------------
 *  Name:   Game.h
 *  Desc:   ”Œœ∑∂‘œÛ
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#ifndef __SHOOT2D_GAME_H__
#define __SHOOT2D_GAME_H__

#include "cocos2d.h"

class Game : public cocos2d::Object
{
public:
	Game();
	virtual ~Game();

	virtual bool init();
	virtual void update(float dt);

	static Game& getInstance();
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SHOOT2D_GAME_H__