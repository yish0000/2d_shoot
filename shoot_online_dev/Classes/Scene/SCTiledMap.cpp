/*
 * ------------------------------------------------------------------------
 *  Name:   SCTiledMap.cpp
 *  Desc:   Tiled map 地图对象
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#include "SCTiledMap.h"

USING_NS_CC;

SCTiledMap::SCTiledMap(int mapId)
	: m_iMapID(mapId), m_sMapFile(""), m_fScale(1.0f)
{
}

SCTiledMap::~SCTiledMap()
{
}

bool SCTiledMap::init()
{
	// Fixme, 加载地图配置模板
	// 

	// 加载场景对象数据


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