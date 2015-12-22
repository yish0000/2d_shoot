/*
 * ------------------------------------------------------------------------
 *  Name:   SCTiledMap.cpp
 *  Desc:   Tiled map 地图对象
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#include "SCTiledMap.h"
#include "SCSceneBase.h"
#include "Data/SCDataModule.h"
#include "Main/SCConfigs.h"
#include "Utility/SCUtilityFunc.h"
#include "Utility/SCGeometry.h"
#include "cocos2d.h"

USING_NS_CC;

SCTiledMap::SCTiledMap(int mapId)
	: m_iMapID(mapId), m_sMapFile(""), m_fScaleFactor(1.0f), m_fEffectLayerZ(100)
	, m_pBackEffectLayer(NULL), m_pFrontEffectLayer(NULL), m_pTargetNode(NULL)
	, m_pMoveMapAction(NULL), m_pScaleAction(NULL), m_bFocusing(false)
{
}

SCTiledMap::~SCTiledMap()
{
}

SCTiledMap* SCTiledMap::create(int mapId)
{
	SCTiledMap* pMap = new SCTiledMap(mapId);
	if( pMap && pMap->init() )
	{
		pMap->autorelease();
		return pMap;
	}
	else
	{
		delete pMap;
		return NULL;
	}
}

bool SCTiledMap::init()
{
	// 取Map模板数据
	WORLD_ESSENCE* pTempl = (WORLD_ESSENCE*)glb_getDataModule()->getTemplate(m_iMapID, DT_WORLD_ESSENCE);
	if (!pTempl)
	{
		CCLOG("SCTiledMap::init, unknown world id(%d)", m_iMapID);
		return false;
	}

	m_sMapFile = pTempl->map_path;

	// 加载TMX地图
	if( !initWithTMXFile(m_sMapFile) )
	{
		CCLOG("SCTiledMap::init, failed to load the TMX file (%s)!", m_sMapFile.c_str());
		return false;
	}

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
			m_collisions.push_back(pCollision);
			pObj = pCollision;
		}
        else if( group == "climb" )
        {
            SCTMClimb* pClimb = new SCTMClimb();
            m_climbs.push_back(pClimb);
            pObj = pClimb;
        }
		else if( group == "npc" )
		{
			SCTMNPC* pNPC = new SCTMNPC();
			if( dic.find("tid") == dic.end() )
			{
				delete pNPC;
				CCLOG("SCTileMap::addObjectGroup, tid of the npc cannot be null!");
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
                delete pOrnament;
                CCLOG("SCTiledMap::addObjectGroup, gfx of ornament must not be null!");
                return;
			}
			pOrnament->m_gfx = dic["gfx"].asString();
            
            if( dic.find("layer") == dic.end() )
                pOrnament->m_layer = "rd_add";
            else
                pOrnament->m_layer = dic["layer"].asString();
            if( dic.find("scale") != dic.end() )
                pOrnament->m_fScale = dic["scale"].asFloat();
			m_ornaments.push_back(pOrnament);
			pObj = pOrnament;
		}
        else if( group == "platform" )
        {
            SCTMPlatform* pPlatform = new SCTMPlatform();
            if( dic.find("tid") == dic.end() )
            {
                delete pPlatform;
                CCLOG("SCTiledMap::addObjectGroup, tid of the platform cannot be null!");
                return;
            }
            
            pPlatform->m_iTID = dic["tid"].asInt();
            m_platforms.push_back(pPlatform);
            pObj = pPlatform;
        }
		else if( group == "obstacle" )
		{
			SCTMObstacle* pObstacle = new SCTMObstacle();
			if( dic.find("tid") == dic.end() )
			{
				delete pObstacle;
				CCLOG("SCTiledMap::addObjectGroup, tid of the obstacle cannot be null!");
				return;
			}

			pObstacle->m_iTID = dic["tid"].asInt();
			m_obstacles.push_back(pObstacle);
			pObj = pObstacle;
		}
        else if( group == "player" )
        {
            SCTMPlayer* pPlayer = new SCTMPlayer();
            m_players.push_back(pPlayer);
            pObj = pPlayer;
        }
        else if( group == "transport" )
        {
            SCTMTransport* pTransport = new SCTMTransport();
            m_transports.push_back(pTransport);
            pObj = pTransport;
        }
		else
		{
			CCLOG("SCTiledMap::addObjectGroup, unknown object group (%s)", group.c_str());
			return;
		}

		if( pObj )
		{
			pObj->m_pos.set(x, y);
			pObj->m_boundingBox.setRect(x, y, width, height);
		}
	}
}

void SCTiledMap::update(float dt)
{
	updateCamera(dt);
	updateLayerPosition(dt);
	updateEffectLayer(dt);
}

// 更新相机位置
void SCTiledMap::updateCamera(float dt)
{
	if( !m_pTargetNode || m_bFocusing )
		return;

	Size winSize = Director::getInstance()->getWinSize();
	Point screenCenter = Point(winSize.width / 2, winSize.height / 2);

	Point targetPos = m_pTargetNode->getPosition();
	float newX = (-targetPos.x + screenCenter.x / getScale()) * getScale();
	float newY = (-targetPos.y + winSize.height * 0.382f / getScale()) * getScale();
	newX = clampf(newX, (-m_realSize.width + winSize.width / getScale()) * getScale(), 0);
	newY = clampf(newY, (-m_realSize.height + screenCenter.y / getScale()) * getScale(), 0);
	Point pos = getPosition();
	setPosition(Point(pos.x + (newX - pos.x) / 5, pos.y + (newY - pos.y) / 5));
}

// 更新各个层的位置
void SCTiledMap::updateLayerPosition(float dt)
{
	Point basePos = getPosition();
	float fScale = getScale();

	std::map<std::string, LayerList>::iterator it;
	for(it=m_layers.begin(); it!=m_layers.end(); ++it)
	{
		LayerList& layerList = it->second;
		if( layerList.size() > 0 )
		{
			// Add层 X, Y速度
			float baseSpeedRatioX = (m_layerPropCache[layerList[0]].mask & MASK_SPEEDX) ? m_layerPropCache[layerList[0]].speedX : 1.0f;
			float baseSpeedRatioY = (m_layerPropCache[layerList[0]].mask & MASK_SPEEDY) ? m_layerPropCache[layerList[0]].speedY : 1.0f;

			// 调整位置
			LayerNodeList layerNodes = m_layerNodes[it->first];
			for(size_t i=0; i<layerList.size(); ++i)
			{
				TMXLayer* baseLayer = layerList[i];
				TMXLayer* loopLayer = m_loopLayers[layerList[i]];

				Point bpos = baseLayer->getPosition();
				Point lpos(0, 0);
				if( loopLayer )
					lpos = loopLayer->getPosition();

				LayerProperty property = m_layerPropCache[layerList[i]];
				
				// X方向
				float speedRatioX = (property.mask & MASK_SPEEDX) ? property.speedX : baseSpeedRatioX;

				// 按循环速度调整位置
				if( property.mask & MASK_LOOPX )
				{
					property.distX = property.distX + property.loopX * dt;
					property.distLoopX = property.distLoopX + property.loopY * dt;

					if( property.loopX > 0 )
					{
						if( property.distX > m_realSize.width )
							property.distX = property.distX - 2 * m_realSize.width;
						if( property.distLoopX > m_realSize.width )
							property.distLoopX = property.distLoopX - 2 * m_realSize.width;
					}
					else
					{
						if( property.distX < -m_realSize.width )
							property.distX = property.distX + 2 * m_realSize.width;
						if( property.distLoopX < -m_realSize.width )
							property.distLoopX = property.distLoopX + 2 * m_realSize.width;
					}

					bpos.x = basePos.x / fScale * (speedRatioX-1) + property.distX;
					lpos.x = basePos.x / fScale * (speedRatioX-1) + property.distLoopX;
				}
				else
				{
					bpos.x = basePos.x / fScale * (speedRatioX-1);
					lpos.x = bpos.x;
				}

				// Y方向
				float speedRatioY = (property.mask & MASK_SPEEDY) ? property.speedY : baseSpeedRatioY;

				// 按循环速度调整位置
				if( property.mask & MASK_LOOPY )
				{
					property.distY = property.distY + property.loopX * dt;
					property.distLoopY = property.distLoopY + property.loopX * dt;
					if( property.loopX > 0 )
					{
						if( property.distY > m_realSize.height )
							property.distY = property.distY - 2 * m_realSize.height;
						if( property.distLoopY > m_realSize.height )
							property.distLoopY = property.distLoopY - 2 * m_realSize.height;
					}
					else
					{
						if( property.distY < -m_realSize.height )
							property.distY = property.distY + 2 * m_realSize.height;
						if( property.distLoopY < -m_realSize.height )
							property.distLoopY = property.distLoopY + 2 * m_realSize.height;
					}

					bpos.y = basePos.y / fScale * (speedRatioY-1) + property.distY;
					lpos.y = basePos.y / fScale * (speedRatioY-1) + property.distLoopY;
				}
				else
				{
					bpos.y = basePos.y / fScale * (speedRatioY-1);
					lpos.y = bpos.y;
				}

				baseLayer->setPosition(bpos);
				layerNodes[i]->setPosition(bpos);
				if( loopLayer ) loopLayer->setPosition(lpos);
			}
		}
	}
}

// 更新特效层位置，始终让特效层在屏幕中间
void SCTiledMap::updateEffectLayer(float dt)
{
	Layer* backEffectLayer = getBackEffectLayer();
	Point point = convertToWorldSpace(Point(0, 0));
	float scale = getScale();
	backEffectLayer->setScale(1 / scale);
	backEffectLayer->setPosition(-point.x / scale, -point.y / scale);
}

Point SCTiledMap::getWorldPosByScreenPos(const Point& pos)
{
	return Point(
		(pos.x - getPosition().x) / getScale(), (pos.y - getPosition().y) / getScale());
}

Point SCTiledMap::getScreenPosByWorldPos(const Point& pos)
{
	return Point(
		(getScale() * pos.x + getPosition().x), (getScale() * pos.y + getPosition().y));
}

Layer* SCTiledMap::getFrontEffectLayer()
{
	if( !m_pFrontEffectLayer )
	{
		Size winSize = Director::getInstance()->getWinSize();
		m_pFrontEffectLayer = Layer::create();
		m_pFrontEffectLayer->setAnchorPoint(Point(0, 0));
		m_pFrontEffectLayer->setPosition(Point(0, 0));
		m_pFrontEffectLayer->setCascadeOpacityEnabled(true);
		m_pFrontEffectLayer->setContentSize(winSize);
		glb_getCurScene()->addChild(m_pFrontEffectLayer, SCENELAYER_ZORDER_UI + 1);
	}

	return m_pFrontEffectLayer;
}

Layer* SCTiledMap::getBackEffectLayer()
{
	if( !m_pBackEffectLayer )
	{
		Size winSize = Director::getInstance()->getWinSize();
		m_pBackEffectLayer = Layer::create();
		m_pBackEffectLayer->setAnchorPoint(Point(0, 0));
		m_pBackEffectLayer->setPosition(Point(0, 0));
		m_pBackEffectLayer->setCascadeOpacityEnabled(true);
		m_pBackEffectLayer->setContentSize(winSize);
		addChild(m_pBackEffectLayer, m_fEffectLayerZ);
	}

	return m_pBackEffectLayer;
}

void SCTiledMap::addTMXLayer(const std::string& layerName)
{
	if( m_layers.find(layerName) == m_layers.end() )
	{
		m_layers[layerName] = LayerList();
	}

	if( m_layerNodes.find(layerName) == m_layerNodes.end() )
	{
		m_layerNodes[layerName] = LayerNodeList();
	}

	TMXLayer* pLayerAdd = getLayer(layerName + "_add");
	if( pLayerAdd )
	{
		Texture2D* pTexture = pLayerAdd->getTexture();
		if( pTexture ) pTexture->setAntiAliasTexParameters();

		Value propCount = pLayerAdd->getProperty("count");
		int count = propCount.isNull() ? 0 : propCount.asInt();

		// 将add层加入到表中
		addLayerImp(pLayerAdd, layerName, "_add", count == 0);

		for(int i=1; i<=count; i++)
		{
			TMXLayer* pLayer = getLayer(layerName + StringUtils::toString(i));
			if( pLayer )
			{
				Texture2D* pTexture = pLayer->getTexture();
				if( pTexture ) pTexture->setAntiAliasTexParameters();

				if( i == count )
					addLayerImp(pLayer, layerName, StringUtils::toString(i), true);
				else
					addLayerImp(pLayer, layerName, StringUtils::toString(i), false);
			}
			else
			{
				std::string strSubLayer = layerName + StringUtils::toString(i);
				CCLOG("SCTiledMap::addTMXLayer, %s lost sub layer %s, please check the add layer's count property!", m_sMapFile.c_str(), strSubLayer.c_str());
			}
		}
	}
}

void SCTiledMap::addLayerImp(cocos2d::TMXLayer* pLayer, const std::string& name, const std::string& suffix, bool bLast)
{
	// 添加层
	m_layers[name].push_back(pLayer);

	Node* pLayerNode = Node::create();
	addChild(pLayerNode, pLayer->getLocalZOrder());

	m_layerNodes[name].push_back(pLayerNode);
	m_nodeTable[name + suffix] = pLayerNode;
	cacheLayerProperty(pLayer);

	LayerProperty prop = m_layerPropCache[pLayer];

	// 设置颜色
	if( prop.mask & MASK_COLOR )
	{
		setLayerColor(pLayer, prop.color);
	}

	if( (prop.mask & MASK_LOOPX) || (prop.mask & MASK_LOOPY) )
	{
		std::string loopLayerName = name + suffix + "_loop";
		TMXLayer* pLoopLayer = getLayer(loopLayerName);
		if( !pLoopLayer )
			CCLOG("SCTiledMap::addLayerImp, Map (%s) lost the loop layer (%s)", m_sMapFile.c_str(), loopLayerName.c_str());
		else
		{
			Texture2D* pTexture = pLoopLayer->getTexture();
			if( pTexture )
				pTexture->setAntiAliasTexParameters();

			m_loopLayers[pLayer] = pLoopLayer;

			// 设置颜色
			if( prop.mask & MASK_COLOR )
			{
				setLayerColor(pLoopLayer, prop.color);
			}
		}
	}

	// 在rd层的最后一层添加Effect背景层
	if( name == "rd" )
	{
		if( m_fEffectLayerZ == 0.0f )
			m_fEffectLayerZ = 100.0f;
		if( pLayer->getLocalZOrder() < m_fEffectLayerZ )
			m_fEffectLayerZ = pLayer->getLocalZOrder();
		if( bLast )
			m_fEffectLayerZ = m_fEffectLayerZ - 1;
	}
}

// 缓存地图层的属性
void SCTiledMap::cacheLayerProperty(cocos2d::TMXLayer* pLayer)
{
	LayerProperty prop;

	if( !pLayer->getProperty("colorr").isNull() )
	{
		prop.mask |= MASK_COLOR;
		prop.color.r = pLayer->getProperty("colorr").asByte();
		prop.color.g = pLayer->getProperty("colorg").asByte();
		prop.color.b = pLayer->getProperty("colorb").asByte();
	}

	if( !pLayer->getProperty("loopx").isNull() )
	{
		prop.mask |=  MASK_LOOPX;
		prop.loopX = pLayer->getProperty("loopx").asInt();
		prop.distX = 0;
		prop.distLoopX = m_realSize.width;
	}

	if( !pLayer->getProperty("loopy").isNull() )
	{
		prop.mask |= MASK_LOOPY;
		prop.loopY = pLayer->getProperty("loopy").asInt();
		prop.distY = 0;
		prop.distLoopY = m_realSize.height;
	}

	Value propSpeedX = pLayer->getProperty("speedx");
	if( !propSpeedX.isNull() )
	{
		prop.mask |= MASK_SPEEDX;
		prop.speedX = propSpeedX.asFloat();
	}

	Value propSpeedY = pLayer->getProperty("speedy");
	if( !propSpeedY.isNull() )
	{
		prop.mask |= MASK_SPEEDY;
		prop.speedY = propSpeedY.asFloat();
	}

	m_layerPropCache[pLayer] = prop;
}

// 显示包围盒
void SCTiledMap::showBoundingBox()
{
	for(auto& col : m_collisions)
	{
		RectShape* pRect = RectShape::create(col->m_boundingBox.size);
		pRect->setContentSize(col->m_boundingBox.size);
		pRect->setAnchorPoint(Point(0, 0));
		pRect->setPosition(col->m_boundingBox.origin.x, col->m_boundingBox.origin.y);
		pRect->setLineColor(Color4F(1.0, 0.0, 0.0, 1.0));
		addChildToLayer(pRect, "rd_add");
	}

	for(auto& climb : m_climbs)
	{
		RectShape* pRect = RectShape::create(climb->m_boundingBox.size);
		pRect->setContentSize(climb->m_boundingBox.size);
		pRect->setAnchorPoint(Point(0, 0));
		pRect->setPosition(climb->m_boundingBox.origin.x, climb->m_boundingBox.origin.y);
		pRect->setLineColor(Color4F(1.0f, 0.0f, 0.0f, 1.0f));
		addChildToLayer(pRect, "rd_add");
	}
}

// 添加child到指定层
bool SCTiledMap::addChildToLayer(cocos2d::Node* child, const std::string& layerName, float z)
{
	Node* pLayer = m_nodeTable[layerName];
	if( pLayer )
	{
		pLayer->addChild(child, z);
		return true;
	}
	else
	{
		CCLOG("SCTiledMap::addChildToLayer, failed to add child node to layer(%s) on map(%s)!", layerName.c_str(), m_sMapFile.c_str());
		return false;
	}
}

// 设置层的颜色
void SCTiledMap::setLayerColor(cocos2d::TMXLayer* pLayer, const cocos2d::Color3B& color)
{
	Size mapSize = getMapSize();
	for(size_t i=0; i<mapSize.width; ++i)
	{
		for(size_t j=0; j<mapSize.height; ++j)
		{
			Sprite* pTile = pLayer->getTileAt(Point(i, j));
			if( pTile )
				pTile->setColor(color);
		}
	}
}

// 地图震动
void SCTiledMap::shake(float fTime)
{
	// 震动
	getParent()->runAction(
		Repeat::create(Sequence::create(MoveBy::create(0.05f, Point(-10,-10)), MoveBy::create(0.05f, Point(10,10)), nullptr), fTime * 10)
	);

	// 恢复原位
	Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(SCTiledMap::shakeStop, this), this,
		fTime + 0.001f, 1, true, false, "RestoreShake");
}

void SCTiledMap::shakeStop(float dt)
{
	getParent()->setPosition(0, 0);
}

// 跟踪指定节点
void SCTiledMap::followNode(cocos2d::Node* pNode)
{
	m_pTargetNode = pNode;
}

// 设置缩放系数
void SCTiledMap::setScaleFactor(float fScale)
{
	m_fScaleFactor = fScale;
	setScale(m_fScaleFactor);
}

// 聚焦地图上某点
void SCTiledMap::runFocusAction(float fTime, int x, int y, float fScale, const std::function<void(void)>& callback)
{
	stopFocusAction();

	if( fScale != 0.0f )
		fScale = fScale * m_fScaleFactor;
	else
		fScale = getScale();

	Size winSize = Director::getInstance()->getWinSize();
	Point screenCenter = Point(winSize.width / 2, winSize.height / 2);

	float newX = (-x + screenCenter.x / fScale) * fScale;
	float newY = (-y + winSize.height * 0.382f / fScale) * fScale;
	newX = clampf(newX, (-m_realSize.width + winSize.width / fScale) * fScale, 0.0f);
	newY = clampf(newY, (-m_realSize.height + screenCenter.y / fScale) * fScale, 0.0f);

	m_pMoveMapAction = Sequence::create(
		Spawn::createWithTwoActions(EaseExponentialOut::create(MoveTo::create(fTime, Point(newX, newY))), EaseExponentialOut::create(ScaleTo::create(fTime, fScale))), 
		CallFunc::create([&] {
			m_pMoveMapAction = nullptr;
			if( callback )
				callback();
		}), nullptr);
	runAction(m_pMoveMapAction);

	m_bFocusing = true;
}

// 取消聚焦回到原点
void SCTiledMap::runUnfocusAction(float fTime, const std::function<void(void)>& callback)
{
	stopFocusAction();

	if( !m_pTargetNode )
		return;

	float fScale = m_fScaleFactor;
	Size winSize = Director::getInstance()->getWinSize();
	Point screenCenter = Point(winSize.width / 2, winSize.height / 2);

	Point targetPos = m_pTargetNode->getPosition();
	float newX = (-targetPos.x + screenCenter.x / fScale) * fScale;
	float newY = (-targetPos.y + winSize.height * 0.382f / fScale) * fScale;
	newX = clampf(newX, (-m_realSize.width + winSize.width / fScale) * fScale, 0.0f);
	newY = clampf(newY, (-m_realSize.height + screenCenter.y / fScale) * fScale, 0.0f);

	m_pMoveMapAction = Sequence::create(
		Spawn::createWithTwoActions(
			EaseExponentialOut::create(MoveTo::create(fTime, Point(newX, newY))), 
			EaseExponentialOut::create(ScaleTo::create(fTime, fScale))
		), 
		CallFunc::create([&] {
			m_pMoveMapAction = nullptr;
		}), nullptr);
	runAction(m_pMoveMapAction);
	m_bFocusing = true;
}

// 取消聚焦地图上的焦点
void SCTiledMap::stopFocusAction()
{
	if( m_pMoveMapAction )
	{
		stopAction(m_pMoveMapAction);
		m_pMoveMapAction = NULL;
	}
}

// 执行缩放动作
void SCTiledMap::runScaleAction(float fTime, float fScale, const std::function<void(void)>& callback)
{
	stopScaleAction();

	m_pScaleAction = Sequence::create(
		EaseExponentialOut::create(ScaleTo::create(fTime, fScale)),
		CallFunc::create([&] {
			m_pScaleAction = NULL;
			if( callback )
				callback();
		}), nullptr);
	runAction(m_pScaleAction);
}

// 取消缩放动作
void SCTiledMap::runUnscaleAction(float fTime, const std::function<void(void)>& callback)
{
	stopScaleAction();

	m_pScaleAction = Sequence::create(
		EaseExponentialOut::create(ScaleTo::create(fTime, m_fScaleFactor)),
		CallFunc::create([&] {
			m_pScaleAction = NULL;
			if( callback )
				callback();
		}), nullptr);
	runAction(m_pScaleAction);
}

// 停止当前缩放动作
void SCTiledMap::stopScaleAction()
{
	if( m_pScaleAction )
	{
		stopAction(m_pScaleAction);
		m_pScaleAction = NULL;
	}
}

// 获取layer节点
cocos2d::Node* SCTiledMap::getLayerNode(const std::string& name)
{
	std::map<std::string, cocos2d::Node*>::iterator it = m_nodeTable.find(name);
	return it != m_nodeTable.end() ? it->second : NULL;
}

// 检查包围盒碰撞
bool SCTiledMap::checkCollision(const cocos2d::Rect& boundingBox)
{
	for(auto& col : m_collisions)
	{
		if( SCGeometry::bbIntersects(col->m_boundingBox, boundingBox) )
			return true;
	}

	return false;
}

// 检测包围盒下边是否有碰撞
bool SCTiledMap::checkBottomCollision(const cocos2d::Rect& boundingBox, float xDist, float yDist, float& collisionY)
{
	cocos2d::Rect rcBound = boundingBox;
	rcBound.origin.x = rcBound.origin.x + xDist;
	rcBound.origin.y = rcBound.origin.y - yDist;
	rcBound.size.height = rcBound.size.height + yDist;

	bool isCollision = false;
	collisionY = 0;
	for(auto& v : m_collisions)
	{
		// 只考虑位置在包围盒下面的
		if( v->m_boundingBox.origin.y + v->m_boundingBox.size.height < boundingBox.origin.y )
		{
			if( SCGeometry::bbIntersects(v->m_boundingBox, rcBound) )
			{
				// 取最近的碰撞位置
				if( v->m_boundingBox.origin.y + v->m_boundingBox.size.height > collisionY )
				{
					isCollision = true;
					collisionY = v->m_boundingBox.origin.y + v->m_boundingBox.size.height;
				}
			}
		}
	}

	return isCollision;
}

// 检查包围盒左边是否有碰撞
bool SCTiledMap::checkLeftCollision(const cocos2d::Rect& boundingBox, float xDist, float yDist, float& collisionX)
{
	cocos2d::Rect rcBound = boundingBox;
	rcBound.origin.x = rcBound.origin.x - xDist;
	rcBound.origin.y = rcBound.origin.y - yDist;
	rcBound.size.width = rcBound.size.width + xDist;

	bool isCollision = false;
	for(auto& v : m_collisions)
	{
		// 只考虑位置在包围盒左面的
		if( v->m_bXCollision && v->m_boundingBox.origin.x + v->m_boundingBox.size.width < boundingBox.origin.x )
		{
			if( SCGeometry::bbIntersects(v->m_boundingBox, rcBound) )
			{
				// 取最近的碰撞位置
				if( v->m_boundingBox.origin.x + v->m_boundingBox.size.width > collisionX ) 
				{
					isCollision = true;
					collisionX = v->m_boundingBox.origin.x + v->m_boundingBox.size.width;
				}
			}
		}
	}

	return isCollision;
}

// 检查包围盒右边是否有碰撞
bool SCTiledMap::checkRightCollision(const cocos2d::Rect& boundingBox, float xDist, float yDist, float& collisionX)
{
	cocos2d::Rect rcBound = boundingBox;
	rcBound.origin.y = rcBound.origin.y - yDist;
	rcBound.size.width = rcBound.size.width + xDist;

	bool isCollision = false;
	collisionX = 100000.0f;
	for(auto& v : m_collisions)
	{
		// 只考虑位置在包围盒右面的
		if( v->m_bXCollision && v->m_boundingBox.origin.x > rcBound.origin.x + boundingBox.size.width )
		{
			if( SCGeometry::bbIntersects(v->m_boundingBox, rcBound) )
			{
				// 取最近的碰撞位置
				if( v->m_boundingBox.origin.x < collisionX )
				{
					isCollision = true;
					collisionX = v->m_boundingBox.origin.x;
				}
			}
		}
	}

	return isCollision;
}

// 检查包围盒攀爬
bool SCTiledMap::checkClimb(const cocos2d::Rect& boundingBox)
{
	for(auto& v : m_climbs )
	{
		if( SCGeometry::bbIntersects(v->m_boundingBox, boundingBox) )
			return true;
	}

	return false;
}

// 检查包围盒下面是否可攀爬
bool SCTiledMap::checkBottomClimb(const cocos2d::Rect& boundingBox, float xDist, float yDist, float& climbY)
{
	cocos2d::Rect rcBound;
	rcBound.origin.x = boundingBox.origin.x - xDist;
	rcBound.origin.y = boundingBox.origin.y - yDist;
	rcBound.size.height = boundingBox.size.height + yDist;

	bool isClimb = false;
	climbY = 0;
	for(auto& v : m_climbs)
	{
		// 只考虑位置在包围盒下面的
		if( v->m_boundingBox.origin.y + v->m_boundingBox.size.height < boundingBox.origin.y )
		{
			if( SCGeometry::bbIntersects(v->m_boundingBox, boundingBox) )
			{
				// 取最近的碰撞位置
				if( v->m_boundingBox.origin.y + v->m_boundingBox.size.height > climbY )
				{
					isClimb = true;
					climbY = v->m_boundingBox.origin.y + v->m_boundingBox.size.height;
				}
			}
		}
	}

	return isClimb;
}