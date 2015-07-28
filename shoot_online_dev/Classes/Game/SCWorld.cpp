//
//  world.cpp
//  ShootOnline
//
//  Created by 琰 陈 on 15/6/18.
//
//

#include "SCWorld.h"
#include "Scene/SCSceneBase.h"
#include "Utility/SCRandomGen.h"

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
            //TODO :
            return nullptr;
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
SCWorld::SCWorld() : m_pTileMap(NULL), m_pHostPlayer(NULL)
{
    _msg_queue = new MessageQueueList(this);
}

SCWorld::~SCWorld()
{
}

bool SCWorld::init()
{
	if (!Node::init())
		return false;

    SCRandomGen::Init();
	m_pTileMap = SCTiledMap::create(0);
	addChild(m_pTileMap);

	// 加载主玩家
	m_pHostPlayer = SCHostPlayer::create();
	m_pTileMap->addChildToLayer(m_pHostPlayer, "rd_add", SCENELAYER_ZORDER_HOSTPLAYER);
	m_pHostPlayer->setPosition(300, 120);

	// 地图跟随主角
	m_pTileMap->followNode(m_pHostPlayer);
    return true;
}

void SCWorld::SendMessage(const Message& msg)
{
    _msg_queue->AddMessage(msg);
}

void SCWorld::SendMessage(const std::vector<GID> &glist, const Message& msg)
{
    _msg_queue->AddMuiltiMessage(glist,msg);
}


void SCWorld::DispatchMessage(const Message &msg)
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
	m_pHostPlayer->update(dt);
	m_pTileMap->update(dt);

    _msg_queue->update(dt);
    _npc_manager.update(dt);
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