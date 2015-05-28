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

void SCTiledMap::addObjectGroup(const std::string& group)
{
	TMXObjectGroup* pGroup = getObjectGroup(group);
	if( !pGroup ) return;

	ValueVector& objects = pGroup->getObjects();
	for(size_t i=0; i<objects.size(); ++i)
	{
		ValueMap& dic = objects[i].asValueMap();
		int x = dic["x"].asInt();
		int y = dic["y"].asInt();
		int width = dic["width"].asInt();
		int height = dic["height"].asInt();

		SCTMObject* pObj = NULL;
		if( group == "collision" )
		{
			SCTMCollision* pCollision = new SCTMCollision();
			pCollision->m_bXCollision = dic["xcollision"].asBool();
			m_conllisions.push_back(pCollision);
			pObj = pCollision;
		}
		else if( group == "npc" )
		{
			SCTMNPC* pNPC = new SCTMNPC();
			if( dic.find("tid") == dic.end() )
			{
				delete pNPC;
				CCLOG("tid of the npc cannot be null!");
				return;
			}
			pNPC->m_iTID = dic["tid"].asInt();
			m_npcs.push_back(pNPC);
			pObj = pNPC;
		}
		else if( group == "ornament" )
		{
			SCTMOrnament* pOrnament = new SCTMOrnament();
			if( dic.find("gfx") == dic.end() )
			{
				
			}
			pOrnament->m_gfx = dic["gfx"].asString();
			pOrnament->m_layer = dic[""]
		}

		pObj->m_pos.set(x, y);
		pObj->m_boundingBox.setRect(x, y, width, height);
	}
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