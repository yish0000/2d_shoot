﻿/*
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
		TM_OBJ_CLIMB,		// 攀爬物
		TM_OBJ_NPC,			// 刷怪点
		TM_OBJ_ORNAMENT,	// 装饰物
		TM_OBJ_PLATFORM,	// 移动平台
		TM_OBJ_OBSTACLE,	// 阻挡物
		TM_OBJ_PLAYER,		// 玩家出生点
		TM_OBJ_TRANSPORT,	// 传送点
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
	SCTMCollision() : SCTMObject(TM_OBJ_COLLISION), m_bXCollision(false) {}

public:
	bool m_bXCollision;
};

/** 攀爬物
*/
class SCTMClimb : public SCTMObject
{
public:
	SCTMClimb() : SCTMObject(TM_OBJ_CLIMB) {}
};

/** NPC位置
*/
class SCTMNPC : public SCTMObject
{
public:
    SCTMNPC() : SCTMObject(TM_OBJ_NPC), m_iTID(-1) {}

public:
	int m_iTID;		// NPC模板ID
};

/** 装饰物
*/
class SCTMOrnament : public SCTMObject
{
public:
	SCTMOrnament() : SCTMObject(TM_OBJ_ORNAMENT), m_fScale(1.0f) {}

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
	SCTMPlatform() : SCTMObject(TM_OBJ_PLATFORM), m_iTID(-1) {}

public:
	int m_iTID;
};

/** 阻挡物体
*/
class SCTMObstacle : public SCTMObject
{
public:
	SCTMObstacle() : SCTMObject(TM_OBJ_OBSTACLE), m_iTID(-1) {}

public:
	int m_iTID;
};

/** 玩家出生点
*/
class SCTMPlayer : public SCTMObject
{
public:
	SCTMPlayer() : SCTMObject(TM_OBJ_PLAYER) {}
};

/** 传送点
*/
class SCTMTransport : public SCTMObject
{
public:
	SCTMTransport() : SCTMObject(TM_OBJ_TRANSPORT) {}
};

///////////////////////////////////////////////////////////////////////////

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
	typedef std::vector<SCTMClimb*> ClimbList;
	typedef std::vector<SCTMNPC*> NPCList;
	typedef std::vector<SCTMOrnament*> OrnamentList;
	typedef std::vector<SCTMPlatform*> PlatformList;
	typedef std::vector<SCTMObstacle*> ObstacleList;
	typedef std::vector<SCTMPlayer*> PlayerList;
	typedef std::vector<SCTMTransport*> TransportList;

public:
	SCTiledMap(int mapId);
	virtual ~SCTiledMap();

	virtual bool init();
	virtual void update(float dt);

	cocos2d::Point getWorldPosByScreenPos(const cocos2d::Point& pos);
	cocos2d::Point getScreenPosByWorldPos(const cocos2d::Point& pos);

	cocos2d::Layer* getFrontEffectLayer();
	cocos2d::Layer* getBackEffectLayer();

	// 震动, (fTime = 持续时间)
	void shake(float fTime);
	// 跟踪指定节点
	void followNode(cocos2d::Node* pNode);
	// 设置缩放系数
	void setScaleFactor(float fScale);

	// 聚焦地图上的某一点
	void runFocusAction(float fTime, int x, int y, float fScale, const std::function<void(void)>& callback);
	void stopFocusAction();
	// 执行缩放动作
	void runScaleAction(float fTime, float fScale, const std::function<void(void)>& callback);
	void runUnscaleAction(float fTime, const std::function<void(void)>& callback);
	void stopScaleAction();

	// 添加子节点到指定的层
	void addChildToLayer(cocos2d::Node* pChild, const std::string& layerName, float zOrder);

	// 检查包围盒碰撞
	bool checkCollision(const cocos2d::Rect& boundingBox);
	bool checkBottomCollision(const cocos2d::Rect& boundingBox, float xDist, float yDist);
	bool checkLeftCollision(const cocos2d::Rect& boundingBox, float xDist, float yDist);
	bool checkRightCollision(const cocos2d::Rect& boundingBox, float xDist, float yDist);

	// 检查是否可攀爬
	bool checkClimb(const cocos2d::Rect& boundingBox);
	bool checkBottomClimb(const cocos2d::Rect& boundingBox, float xDist, float yDist);

	// 获得layer节点
	cocos2d::Node* getLayerNode(const std::string& name);

	cocos2d::Point getPixelPosByTilePos();
	cocos2d::Point getTilePosByPixelPos();

	// 获取地图大小（宽高的Tile数量）
	cocos2d::Size getMapSize() const;
	// 获取Tile的宽高
	cocos2d::Size getTileSize() const;

	uint32_t getRealWidth() const { return m_realSize.width; }
	uint32_t getRealHeight() const { return m_realSize.height; }

	const CollisionList& getCollisionList() const { return m_conllisions; }
	const ClimbList& getClimbList() const { return m_climbs; }
	const NPCList& getNpcPointList() const { return m_npcs; }
	const OrnamentList& getOrnamentList() const { return m_ornaments; }
	const PlatformList& getPlatformList() const { return m_platforms; }
	const ObstacleList& getObstacleList() const { return m_obstacles; }
	const PlayerList& getPlayerPointList() const { return m_players; }
	
	int getMapID() const { return m_iMapID; }
	const std::string& getMapFile() const { return m_sMapFile; }

protected:
	int m_iMapID;					// 场景配置表ID
	std::string m_sMapFile;			// TMX场景文件
	cocos2d::Size m_realSize;		// 地图的真实大小

	std::map<std::string, LayerList> m_layers;
	std::map<std::string, LayerNodeList> m_layerNodes;
	std::map<std::string, cocos2d::Node*> m_nodeTable;

	cocos2d::Layer* m_pFrontEffectLayer;
	cocos2d::Layer* m_pBackEffectLayer;

	LayerPropertyCache m_layerPropCache;

	// 
	std::unordered_map<cocos2d::TMXLayer*, cocos2d::TMXLayer*> m_loopLayers;

	CollisionList m_conllisions;
	ClimbList m_climbs;
	NPCList m_npcs;
	OrnamentList m_ornaments;
	PlatformList m_platforms;
	ObstacleList m_obstacles;
	PlayerList m_players;
	TransportList m_transports;

	cocos2d::Node* m_pTargetNode;	// 跟踪指定的节点
	bool m_bFocusing;				// 正在聚焦操作
	float m_fScaleFactor;			// 缩放系数

protected:
	// 添加Object
	void addObjectGroup(const std::string& group);
	// 添加地图层
	void addTMXLayer(const std::string& layerName);
	void addLayerImp(cocos2d::TMXLayer* pLayer, const std::string& name, const std::string& suffix, bool bLast);
	// 缓存地图层的属性
	void cacheLayerProperty(cocos2d::TMXLayer* pLayer);

	// 显示包围盒
	void showBoundingBox();

	// 设置层的颜色
	void setLayerColor(cocos2d::TMXLayer* pLayer, const cocos2d::Color3B& color);

	// 更新各个层的位置
	void updateLayerPosition(float dt);
	// 更新相机
	void updateCamera(float dt);
	// 更新特效层
	void updateEffectLayer(float dt);

	// 震动停止
	void shakeStop(float dt);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_TILEDMAP_H__