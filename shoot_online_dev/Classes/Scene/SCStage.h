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

	// 碰撞检测的结果
	struct CollisionResult
	{
		bool leftCollision;
		bool rightCollision;
		bool bottomCollision;
		bool leftBottomCollision;
		bool rightBottomCollision;

		float leftCollisionX;
		float bottomCollisionY;
		float rightCollisionX;

		CollisionResult() : leftCollision(false), rightCollision(false), bottomCollision(false),
			leftBottomCollision(false), rightBottomCollision(false), leftCollisionX(0.0f),
			bottomCollisionY(0.0f), rightCollisionX(0.0f)
		{
		}
	};

public:
	SCWorld();
	virtual ~SCWorld();

	CREATE_FUNC(SCWorld);

	virtual bool init();
	virtual void update(float dt);

	SCTiledMap* getTileMap() { return m_pTileMap; }

	// 碰撞检测
	bool checkCollision(const cocos2d::Rect& bb, const cocos2d::Point& oldPos, const cocos2d::Point& newPos,
		CollisionResult& result);

protected:
	int m_iWorldID;
	SCTiledMap* m_pTileMap;

protected:
	void createTileMap();
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_WORLD_H__