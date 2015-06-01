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
#include "Utility/SCConfigs.h"
#include "Utility/SCUtilityFunc.h"
#include "cocos2d.h"

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

		}

		pObj->m_pos.set(x, y);
		pObj->m_boundingBox.setRect(x, y, width, height);
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
			float baseSpeedRatioX = m_layerPropCache[layerList[0]].speedX;
			float baseSpeedRatioY = m_layerPropCache[layerList[0]].speedY;

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
				float speedRatioX = property.speedX ? property.speedX : baseSpeedRatioX;

				// 按循环速度调整位置
				if( property.loopX )
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
				float speedRatioY = property.speedY ? property.speedY : baseSpeedRatioY;
				// 按循环速度调整位置
				if( property.loopY )
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
		glb_getCurScene()->addChild(m_pBackEffectLayer, SCENELAYER_ZORDER_UI + 1);
	}

	return m_pFrontEffectLayer;
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

		for(int i=0; i<count; i++)
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

	// 设置颜色
	Color3B layerColor = m_layerPropCache[pLayer].color;
	if( m_layerPropCache[pLayer].color.r )
	{
		setLayerColor(pLayer, m_layerPropCache[pLayer].color);
	}

// 	table.insert(self.layers[name], layer)
// 		local layerNode = display.newNode()
// self:addChild(layerNode, layer:getZOrder())
// 	 table.insert(self.layersNodes[name], layerNode)
// 	 self.nodesTable[name..suffix] = layerNode
// self:cacheLayerProperty(layer)
// 
// 	 -- 设置颜色
// 	 if self.layerPropertyCache[layer].r then
// self:setLayerColor(layer, ccc3(
// 	 self.layerPropertyCache[layer].r,
// 	 self.layerPropertyCache[layer].g,
// 	 self.layerPropertyCache[layer].b
// 	 )
// 	 )
// 	 end
// 
// 	 -- 查看add是否有循环
// 	 if self.layerPropertyCache[layer].loopx or self.layerPropertyCache[layer].loopy then
// 
// 		 local loopLayer = self:layerNamed(name.. suffix .. "_loop")
// 		 if loopLayer == nil then
// 			 gErrorLog("地图"..self.mapName.."缺少循环层 "..name.. suffix.. "_loop")
// 		 else
// 		 local texture = loopLayer:getTexture()
// 		 if texture then texture:setAntiAliasTexParameters() end
// 
// 			 self.loopLayers[layer] = loopLayer
// 			 -- 设置颜色
// 			 if self.layerPropertyCache[layer].r then
// self:setLayerColor(loopLayer, ccc3(
// 	 self.layerPropertyCache[layer].r,
// 	 self.layerPropertyCache[layer].g,
// 	 self.layerPropertyCache[layer].b
// 	 )
// 	 )
// 	 end
// 	 end
// 	 end
// 
// 	 -- 在rd层的最后一层添加effect背景层
// 	 if name == "rd" then
// 		 self.effectLayerZ = self.effectLayerZ or 100
// 		 if layer:getZOrder() < self.effectLayerZ then
// 			 self.effectLayerZ = layer:getZOrder()
// 			 end
// 
// 			 if last then
// 				 self.effectLayerZ = self.effectLayerZ - 1
// 				 end
// 				 end
}

// 缓存地图层的属性
void SCTiledMap::cacheLayerProperty(cocos2d::TMXLayer* pLayer)
{
	LayerProperty prop;

	if( !pLayer->getProperty("colorr").isNull() )
	{
		prop.color.r = pLayer->getProperty("colorr").asByte();
		prop.color.g = pLayer->getProperty("colorg").asByte();
		prop.color.b = pLayer->getProperty("colorb").asByte();
	}

	if( !pLayer->getProperty("loopx").isNull() )
	{
		prop.loopX = pLayer->getProperty("loopx").asInt();
		prop.distX = 0;
		prop.distLoopX = m_realSize.width;
	}

	if( !pLayer->getProperty("loopy").isNull() )
	{
		prop.loopY = pLayer->getProperty("loopy").asInt();
		prop.distY = 0;
		prop.distLoopY = m_realSize.height;
	}

	Value propSpeedX = pLayer->getProperty("speedx");
	if( !propSpeedX.isNull() ) prop.speedX = propSpeedX.asFloat();
	Value propSpeedY = pLayer->getProperty("speedy");
	if( !propSpeedY.isNull() ) prop.speedY = propSpeedY.asFloat();

	m_layerPropCache[pLayer] = prop;
}

// 显示包围盒
void SCTiledMap::showBoundingBox()
{
	for(auto& col : m_conllisions)
	{
		
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

// 	 local scale = scale and (scale * self.scaleFactor) or self:getScale()
	 // 	 local newX = ( -x + display.cx / scale ) * scale
	 // 	 local newY = ( -y + display.height * 0.382 / scale ) * scale 
	 // 	 newX = clampf(newX, (-self.width + display.width / scale) * scale, 0)
	 // 	 newY = clampf(newY, (-self.height + display.cy / scale) * scale, 0)
	 // 
	 // 	 self.moveMapAction = transition.sequence({
	 // CCSpawn:createWithTwoActions(
	 // CCEaseExponentialOut:create(CCMoveTo:create(time or 1, ccp(newX, newY))), 
	 // CCEaseExponentialOut:create(CCScaleTo:create(time or 1, scale))
	 // 					 ), 
	 // CCCallFunc:create(function ()
	 // 		   self.moveMapAction = nil 
	 // 		   if callback then
	 // 			   callback()
	 // 			   end
	 // 			   end)})
	 // self:runAction(self.moveMapAction)
	 // 
	 // 	 self.focusing = true
	 // 	 end
}

// 取消聚焦地图上的焦点
void SCTiledMap::stopFocusAction()
{
}