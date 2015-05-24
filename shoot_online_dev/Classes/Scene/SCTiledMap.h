/*
 * ------------------------------------------------------------------------
 *  Name:   SCTiledMap.h
 *  Desc:   Tiled map 地图对象
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#ifndef __SC_TILEDMAP_H__
#define __SC_TILEDMAP_H__

#include "2d/CCTMXTiledMap.h"

class SCTiledMap : public cocos2d::TMXTiledMap
{
public:
	SCTiledMap();
	virtual ~SCTiledMap();

	virtual bool init();
	virtual void update(float dt);

	cocos2d::Point getWorldPosByScreenPos(const cocos2d::Point& pos);
	cocos2d::Point getScreenPosByWorldPos(const cocos2d::Point& pos);

	cocos2d::Layer* getFrontEffectLayer();
	cocos2d::Layer* getBackEffectLayer();

	uint32_t getTileWidth() const { return m_BlockSize.width; }
	uint32_t getTileHeight() const { return m_BlockSize.height; }

	int getMapID() const { return m_iMapID; }
	const std::string& getMapFile() const { return m_sMapFile; }

protected:
	int m_iMapID;
	std::string m_sMapFile;
	cocos2d::Size m_BlockSize;		// Tile的宽高
	cocos2d::Size m_BlockCount;		// Tile在X、Y轴上的个数
	cocos2d::Size m_mapSize;		// 地图的真实大小

protected:
	cocos2d::Point getPixelPosByTilePos();
	cocos2d::Point getTilePosByPixelPos();


};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_TILEDMAP_H__