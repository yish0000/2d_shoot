/*
 * ------------------------------------------------------------------------
 *  Name:   SCWorld.h
 *  Desc:   世界对象
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#ifndef __SC_WORLD_H__
#define __SC_WORLD_H__

#include "2d/CCNode.h"
#include "SCTiledMap.h"

class SCWorld : public cocos2d::Node
{
public:
	SCWorld();
	virtual ~SCWorld();

	virtual bool init();
	virtual void update(float dt);

	SCTiledMap* getTileMap() { return m_pTileMap; }

protected:
	int m_iWorldID;
	SCTiledMap* m_pTileMap;

protected:
	void createTileMap();
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_WORLD_H__