﻿//
//  world.cpp
//  ShootOnline
//
//  Created by 琰 陈 on 15/6/18.
//
//

#include "SCWorld.h"
#include "Scene/SCSceneBase.h"
#include "Utility/SCRandomGen.h"
#include "Utility/SCUtilityFunc.h"
#include "Data/SCDataModule.h"
#include "Utility/SCGeometry.h"

USING_NS_CC;
using namespace CocosDenshion;

//private function here:
SCNpc * SCWorld::FindNPCByID(int64_t id)
{
    return _npc_manager.GetByID(id);
}

SCObject* SCWorld::FindObjectByMsg(const Message &msg)
{
    int64_t id = msg.dest.id;
    switch(msg.dest.type)
    {
        case SC_OBJECT_HOSTPLAYER:
        {
            return m_pHostPlayer;
        }
        break;
        case SC_OBJECT_NPC:
        {
            return FindNPCByID(id);
        }
        break;
        default:
            return nullptr;
    }
}

//public function here:
SCWorld::SCWorld(int tid) : m_iWorldID(tid), m_pEssence(NULL), m_pTileMap(NULL), m_pHostPlayer(NULL), npcOriginID(0), bulletOriginID(0)
{
    _msg_queue = new MessageQueueList(this);
}

SCWorld::~SCWorld()
{
	CC_SAFE_DELETE(_msg_queue);
	CC_SAFE_RELEASE(m_pEssence);
}

SCWorld* SCWorld::create(int worldID)
{
	SCWorld* pWorld = new SCWorld(worldID);
	if (pWorld && pWorld->init())
	{
		pWorld->autorelease();
		return pWorld;
	}
	else
	{
		delete pWorld;
		return NULL;
	}
}

bool SCWorld::init()
{
	if (!Node::init())
		return false;

	// 读取模板
	m_pEssence = (WORLD_ESSENCE*)glb_getDataModule()->getTemplate(m_iWorldID, DT_WORLD_ESSENCE);
	if( m_pEssence )
		m_pEssence->retain();
	else
	{
		CCLOG("SCWorld::init, create the world failed! (tid=%d)", m_iWorldID);
		return false;
	}

    SCRandomGen::Init();
	m_pTileMap = SCTiledMap::create(m_iWorldID);
	addChild(m_pTileMap);

	// 加载主玩家
	m_pHostPlayer = SCHostPlayer::create(1001);
	m_pTileMap->addChildToLayer(m_pHostPlayer, "rd_add", SCENELAYER_ZORDER_HOSTPLAYER);
	m_pHostPlayer->setPosition(300, 120);
    m_pHostPlayer->setActive(true);

	// 地图跟随主角
	m_pTileMap->followNode(m_pHostPlayer);

    npcOriginID = 10000;
    bulletOriginID = 80000;

	// 创建NPC
	const SCTiledMap::NPCList& npcList = m_pTileMap->getNpcPointList();
	for(SCTiledMap::NPCList::const_iterator it=npcList.begin(); it!=npcList.end(); ++it)
	{
		SCTMNPC* pNPC = *it;
		GenerateNpc(pNPC->m_iTID, pNPC->m_pos);
	}

    return true;
}

void SCWorld::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    
    if( !m_pEssence->back_music.empty() )
        SimpleAudioEngine::getInstance()->playBackgroundMusic(m_pEssence->back_music.c_str(), true);
}

void SCWorld::onExit()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    Node::onExit();
}

void SCWorld::sendMessage(const Message& msg)
{
    _msg_queue->AddMessage(msg);
}

void SCWorld::sendMessage(const std::vector<GID> &glist, const Message& msg)
{
    _msg_queue->AddMuiltiMessage(glist,msg);
}

void SCWorld::dispatchMessage(const Message &msg)
{
    SCObject *obj = FindObjectByMsg(msg);
    if(obj == nullptr) return;
    
    if(obj->getID() == msg.dest.id)
    {
        int rst = obj->DispatchMessage(msg);
        if(!rst)
        {
            //TODO Assert!
        }
    }
    return;
}

void SCWorld::update(float dt)
{
	if (m_pTileMap)
		m_pTileMap->update(dt);

	if (m_pHostPlayer)
		m_pHostPlayer->update(dt);

    _msg_queue->update(dt);
    _npc_manager.update(dt);
    _bullet_manager.update(dt);
}

bool SCWorld::checkCollision(const cocos2d::Rect& bb, const cocos2d::Point& oldPos,
	const cocos2d::Point& newPos, CollisionResult& result)
{
	float xDist = fabs(oldPos.x - newPos.x);
	float yDist = fabs(oldPos.y - newPos.y);
	if (xDist < 10.0f) xDist = 10.0f;
	if (yDist < 10.0f) yDist = 10.0f;

	float fCollision = 0.0f;
	// 正下地图碰撞
	result.bottomCollision = m_pTileMap->checkBottomCollision(bb, 0, yDist, result.bottomCollisionY);
	// 左下是否有地图碰撞
	result.leftBottomCollision = m_pTileMap->checkBottomCollision(bb, -bb.size.width, yDist, fCollision);
	// 右下是否有地图碰撞
	result.rightBottomCollision = m_pTileMap->checkBottomCollision(bb, bb.size.width, yDist, fCollision);

	// 左右碰撞(横向碰撞需要考虑纵向位移，否则会出现穿透的问题)
	if (newPos.x - oldPos.x > 0)
	{
		// 地图碰撞
		result.rightCollision = m_pTileMap->checkRightCollision(bb, xDist, oldPos.y - newPos.y, result.rightCollisionX);
	}
	else if (newPos.x - oldPos.x < 0)
	{
		// 地图碰撞
		result.leftCollision = m_pTileMap->checkLeftCollision(bb, xDist, oldPos.y - newPos.y, result.leftCollisionX);
	}

	if (result.bottomCollision || result.leftBottomCollision || result.rightBottomCollision ||
		result.leftCollision || result.rightCollision)
		return true;
	else
		return false;
}



bool SCWorld::checkNPCCollision(const cocos2d::Rect& bb, const cocos2d::Point& oldPos, const cocos2d::Point& newPos,
	std::vector<int64_t>& npcList)
{
	float xDist = fabs(oldPos.x - newPos.x);
	float yDist = fabs(oldPos.y - newPos.y);
	if (xDist < 10.0f) xDist = 10.0f;
	if (yDist < 10.0f) yDist = 10.0f;

	cocos2d::Rect rcBound = bb;
	rcBound.origin.x += xDist;
	rcBound.origin.y -= yDist;

	std::vector<SCNpc*> npcs;
	_npc_manager.EnumObjects(npcs);
	for (size_t i = 0; i < npcs.size(); ++i)
	{
		SCNpc* pNPC = npcs[i];
        if (!pNPC->isActive()) continue;
		if (SCGeometry::bbIntersects(rcBound, pNPC->getBoundingBox()))
			npcList.push_back(pNPC->getGID().id);
	}

	return !npcList.empty();
}

bool SCWorld::checkPlayerCollision(const cocos2d::Rect& bb, const cocos2d::Point& oldPos, const cocos2d::Point& newPos)
{
    float xDist = fabs(oldPos.x - newPos.x);
    float yDist = fabs(oldPos.y - newPos.y);
    if (xDist < 10.0f) xDist = 10.0f;
    if (yDist < 10.0f) yDist = 10.0f;

    cocos2d::Rect rcBound = bb;
    rcBound.origin.x += xDist;
    rcBound.origin.y -= yDist;

    if (!m_pHostPlayer->isActive()) return false;

    return SCGeometry::bbIntersects(rcBound, m_pHostPlayer->getBoundingBox());
}

bool SCWorld::GenerateNpc(int tid, const cocos2d::Point& birthPos)
{
    //初始化一个npc
    SCNpc* npc = new SCNpc(GID(SC_OBJECT_NPC, npcOriginID++), tid);
	if (!npc->init())
	{
		delete npc;
		CCLOG("SCWorld::GenerateNpc, initialize the npc failed! (tid=%d)", tid);
		return false;
	}

    npc->setPosition(birthPos.x, birthPos.y);
	m_pTileMap->addChildToLayer(npc, "rd_add", SCENELAYER_ZORDER_NPC);
    npc->setWorld(this);
	npc->setFaceDirection(-1);
    //加入objlist
	_npc_manager.Insert(npc, npc->getID());
    return true;
}

bool SCWorld::GenerateBullet(int tid, const cocos2d::Point& birthPos, SCObject* owner)
{
    //初始化一个子弹
    SCBullet *bullet = new SCBullet(GID(SC_OBJECT_BULLET, bulletOriginID++), tid);
	if (!bullet->init())
	{
		delete bullet;
		CCLOG("SCWorld::GenerateBullet, initialize the bullet failed! (tid=%d)", tid);
		return false;
	}

    //坐标
    bullet->setBirthPos(birthPos);
    bullet->setOwnerType(owner->getType());
	//bullet->setFaceDirection(m_pHostPlayer->getFaceDirection());
    bullet->setFaceDirection(owner->getFaceDirection());
	m_pTileMap->addChildToLayer(bullet, "rd_add", SCENELAYER_ZORDER_SUBOBJECT);
    bullet->setWorld(this);
	_bullet_manager.Insert(bullet, bullet->getID());
    return true;
}

void SCWorld::RemoveNPC(SCNpc *pNpc)
{
	if (pNpc && pNpc->getParent())
		pNpc->removeFromParent();
}

void SCWorld::shake(float fTime)
{
	if (m_pTileMap)
		m_pTileMap->shake(fTime);
}