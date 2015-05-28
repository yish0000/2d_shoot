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

/** 场景中的对象
*/
class SCTMObject
{
public:

	enum
	{
		TM_OBJ_UNKNOWN,

		TM_OBJ_COLLISION,	// 碰撞体
		TM_OBJ_NPC,			// 刷怪点
		TM_OBJ_ORNAMENT,	// 装饰物
		TM_OBJ_PLATFORM,	// 移动平台
		TM_OBJ_OBSTACLE,	// 阻挡物
	};

public:
	SCTMObject(int type) : m_type(type) {}
	int getType() const { return m_type; }

public:
	cocos2d::Point m_pos;
	cocos2d::Rect m_boundingBox;

protected:
	int m_type;
};

/** 碰撞体
*/
class SCTMCollision : public SCTMObject
{
public:
	SCTMCollision() : SCTMObject(TM_OBJ_COLLISION) {}

public:
	bool m_bXCollision;
};

/** NPC位置
*/
class SCTMNPC : public SCTMObject
{
public:
	SCTMNPC() : SCTMObject(TM_OBJ_NPC) {}

public:
	int m_iTID;		// NPC模板ID
};

/** 装饰物
*/
class SCTMOrnament : public SCTMObject
{
public:
	SCTMOrnament() : SCTMObject(TM_OBJ_ORNAMENT) {}

public:
	std::string m_gfx;
	std::string m_layer;
	float m_fScale;
};

/** 移动平台
*/
class SCTMPlatform : public SCTMObject
{
public:
	SCTMPlatform() : SCTMObject(TM_OBJ_PLATFORM) {}

public:
	int m_iTID;
};

/** 阻挡物体
*/
class SCTMObstacle : public SCTMObject
{
public:
	SCTMObstacle() : SCTMObject(TM_OBJ_OBSTACLE) {}

public:
	int m_iTID;
};

/** 地图对象
*/
class SCTiledMap : public cocos2d::TMXTiledMap
{
public:

	typedef std::vector<cocos2d::TMXLayer*> LayerList;
	typedef std::vector<cocos2d::Node*> LayerNodeList;

	// 图层属性
	struct LayerProperty
	{
		cocos2d::Color3B color;
		int loopX;
		int distX;
		int distLoopX;
		int loopY;
		int distY;
		int distLoopY;
		float speedX;
		float speedY;
	};
	typedef std::unordered_map<cocos2d::TMXLayer*, LayerProperty> LayerPropertyCache;

	// 场景对象列表
	typedef std::vector<SCTMCollision*> CollisionList;
	typedef std::vector<SCTMNPC*> NPCList;
	typedef std::vector<SCTMOrnament*> OrnamentList;
	typedef std::vector<SCTMPlatform*> PlatformList;
	typedef std::vector<SCTMObstacle*> ObstacleList;

public:
	SCTiledMap(int mapId);
	virtual ~SCTiledMap();

	virtual bool init();
	virtual void update(float dt);

	void addTMXLayer(const std::string& layerName);

	cocos2d::Point getWorldPosByScreenPos(const cocos2d::Point& pos);
	cocos2d::Point getScreenPosByWorldPos(const cocos2d::Point& pos);

	cocos2d::Layer* getFrontEffectLayer();
	cocos2d::Layer* getBackEffectLayer();

	// 震动, (fTime = 持续时间)
	void shake(float fTime);
	// 跟踪指定节点
	void followNode(cocos2d::Node* pNode);

	uint32_t getTileWidth() const { return m_BlockSize.width; }
	uint32_t getTileHeight() const { return m_BlockSize.height; }

	int getMapID() const { return m_iMapID; }
	const std::string& getMapFile() const { return m_sMapFile; }

protected:
	int m_iMapID;					// 场景配置表ID
	std::string m_sMapFile;			// TMX场景文件
	cocos2d::Size m_BlockSize;		// Tile的宽高
	cocos2d::Size m_BlockCount;		// Tile在X、Y轴上的个数
	cocos2d::Size m_mapSize;		// 地图的真实大小

	std::map<std::string, LayerList> m_layers;
	std::map<std::string, LayerNodeList> m_layerNodes;
	std::map<std::string, cocos2d::Node*> m_nodeTable;

	LayerPropertyCache m_layerPropCache;

	// 
	std::unordered_map<cocos2d::TMXLayer*, cocos2d::TMXLayer*> m_loopLayers;

	CollisionList m_conllisions;
	NPCList m_npcs;
	OrnamentList m_ornaments;
	PlatformList m_platforms;
	ObstacleList m_obstacles;

	float m_fScale;		// 场景的缩放

protected:
	// 加载场景对象数据
	void addObjectGroup(const std::string& group);

	// 更新各个层的位置
	void updateLayerPosition(float dt);
	// 更新相机
	void updateCamera(float dt);
	// 更新特效层
	void updateEffectLayer(float dt);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_TILEDMAP_H__