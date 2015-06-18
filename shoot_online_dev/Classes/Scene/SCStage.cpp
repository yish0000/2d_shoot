/*
 * ------------------------------------------------------------------------
 *  Name:   SCStage.cpp
 *  Desc:   世界对象
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "SCStage.h"

SCStage::SCStage() : m_iWorldID(0), m_pTileMap(NULL)
{
}

SCStage::~SCStage()
{
}

bool SCStage::init()
{
	if( !Node::init() )
		return false;

	m_pTileMap = SCTiledMap::create(0);
	addChild(m_pTileMap);
	return true;
}

void SCStage::update(float dt)
{
	// 更新地图
	m_pTileMap->update(dt);
}

bool SCStage::checkCollision(const cocos2d::Rect& bb, const cocos2d::Point& oldPos,
							 const cocos2d::Point& newPos, CollisionResult& result)
{
	float xDist = fabs(oldPos.x - newPos.x);
	float yDist = fabs(oldPos.y - newPos.y);
	if( xDist < 10.0f ) xDist = 10.0f;
	if( yDist < 10.0f ) yDist = 10.0f;

	float fCollision = 0.0f;
	// 正下地图碰撞
	result.bottomCollision = m_pTileMap->checkBottomCollision(bb, 0, yDist, result.bottomCollisionY);
	// 左下是否有地图碰撞
	result.leftBottomCollision = m_pTileMap->checkBottomCollision(bb, -bb.size.width, yDist, fCollision);
	// 右下是否有地图碰撞
	result.rightBottomCollision = m_pTileMap->checkBottomCollision(bb, bb.size.width, yDist, fCollision);

	// 左右碰撞(横向碰撞需要考虑纵向位移，否则会出现穿透的问题)
	if( newPos.x - oldPos.x > 0 )
	{
		// 地图碰撞
		result.rightCollision = m_pTileMap->checkRightCollision(bb, xDist, oldPos.y - newPos.y, result.rightCollisionX);
	}	
	else if( newPos.x - oldPos.x < 0 )
	{
		// 地图碰撞
		result.leftCollision = m_pTileMap->checkLeftCollision(bb, xDist, oldPos.y - newPos.y, result.leftCollisionX);
	}

	if( result.bottomCollision || result.leftBottomCollision || result.rightBottomCollision ||
		result.leftCollision || result.rightCollision )
		return true;
	else
		return false;
}