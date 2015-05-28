/*
 * ------------------------------------------------------------------------
 *  Name:   SCTiledMap.cpp
 *  Desc:   Tiled map 地图对象
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#include "SCTiledMap.h"
#include "Utility/SCConfigs.h"

USING_NS_CC;

SCTiledMap::SCTiledMap(int mapId)
	: m_iMapID(mapId), m_sMapFile(""), m_fScaleFactor(1.0f)
{
}

SCTiledMap::~SCTiledMap()
{
}

bool SCTiledMap::init()
{
	// Fixme! 取Map模板数据

	cocos2d::Size tileSize = getTileSize();
	cocos2d::Size tileCount = getMapSize();
	m_realSize.width = tileCount.width * tileSize.width;
	m_realSize.height = tileCount.height * tileSize.height;

	// 添加场景对象数据
	addObjectGroup("collision");
	addObjectGroup("climb");
	addObjectGroup("npc");
	addObjectGroup("ornament");
	addObjectGroup("platform");
	addObjectGroup("obstacle");
	addObjectGroup("player");
	addObjectGroup("transport");

	// 必须有一个玩家出生点
	if( m_players.size() == 0 )
	{
		CCLOG("SCTiledMap::init, Must have one player enter point!!");
		return false;
	}

	// 添加地图层
	addTMXLayer("fg");
	addTMXLayer("rd");
	addTMXLayer("mdf");
	addTMXLayer("md");
	addTMXLayer("bgf");
	addTMXLayer("bg");

	if( SCConfigs::getInstance().isShowBoundingBox() )
	{
		showBoundingBox();
	}

	// 缩放系数
//	m_fScaleFactor = templ.scale;
	setScale(m_fScaleFactor);
	return true;
}

void SCTiledMap::update(float dt)
{
}

Point SCTiledMap::getWorldPosByScreenPos(const Point& pos)
{

}

Point SCTiledMap::getScreenPosByWorldPos(const Point& pos)
{
}

Layer* SCTiledMap::getFrontEffectLayer()
{
}

Layer* SCTiledMap::getBackEffectLayer()
{
}

void SCTiledMap::addTMXLayer(const std::string& layerName)
{
	
}

// 显示包围盒
void SCTiledMap::showBoundingBox()
{
	for(auto& col : m_conllisions)
	{
		
	}
}