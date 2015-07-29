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
#include "Utility/SCUtilityFunc.h"
#include "Data/SCDataModule.h"

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
SCWorld::SCWorld(int tid) : m_iWorldID(tid), m_pEssence(NULL), m_pTileMap(NULL), m_pHostPlayer(NULL), npcOriginID(0), bulletOriginID(0)
{
    _msg_queue = new MessageQueueList(this);
}

SCWorld::~SCWorld()
{
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
	m_pEssence->retain();

    SCRandomGen::Init();
	m_pTileMap = SCTiledMap::create(m_iWorldID);
	addChild(m_pTileMap);

	// 加载主玩家
	m_pHostPlayer = SCHostPlayer::create();
	m_pTileMap->addChildToLayer(m_pHostPlayer, "rd_add", SCENELAYER_ZORDER_HOSTPLAYER);
	m_pHostPlayer->setPosition(300, 120);

	// 地图跟随主角
	m_pTileMap->followNode(m_pHostPlayer);

    npcOriginID = 10000;
    bulletOriginID = 80000;
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

bool SCWorld::GenerateNpc(int64_t id, const cocos2d::Point& birthPos)
{
    //获取npc的模板数据
    NPC_ESSENCE *npcData = (NPC_ESSENCE*)glb_getDataModule()->getTemplate(id, DT_NPC_ESSENCE);
    if (!npcData)
    {
        CCLOG("GenerateNpc err! not found Essense! id : %lld", id);
        return false;
    }

    //初始化一个npc
    SCNpc * npc = new SCNpc(GID(SC_OBJECT_NPC, npcOriginID++), id);
    npc->init();
   
    //组装npc数据
    //property
    scComPropertyData data;
    data.atk_mode = npcData->atk_mode;
    data.atk_interval = npcData->atk_interval;
    data.bullet_id = npcData->bullet_id;
    data.name = npcData->name;
    data.max_hp = npcData->max_hp;
    npc->addComponent(SC_COMPONENT_PROPERTY, (void *)(&data));

    //动画
    npc->addComponent(SC_COMPONENT_ARMATURE, (void *)(&(npcData->res_path)));
    //碰撞
    //TODO 包围盒数据不知道从何处获取
    //坐标
    npc->setPosition(birthPos);

    //加入objlist
	_npc_manager.Insert(npc, npc->getID());

    return true;
}

bool SCWorld::GenerateBullet(int64_t id, const cocos2d::Point& birthPos)
{
    //获取子弹的模板数据
    BULLET_ESSENCE *bulletData = (BULLET_ESSENCE*)glb_getDataModule()->getTemplate(id, DT_BULLET_ESSENCE);
    if (!bulletData)
    {
        CCLOG("GenerateBullet err! not found Essense! id : %lld", id);
        return false;
    }

    //初始化一个子弹
    SCBullet *bullet = new SCBullet(GID(SC_OBJECT_BULLET, bulletOriginID++), id);
    bullet->init();

    //组装子弹数据
    //攻击属性
    scComBulletAtkData data;
    data.atk_max = bulletData->atk_max;
    data.atk_min = bulletData->atk_min;
    bullet->addComponent(SC_COMPONENT_BULLET_ATK, (void *)(&data));
    //动画
    bullet->addComponent(SC_COMPONENT_ARMATURE, (void *)(&(bulletData->res_path)));
    //碰撞
    //TODO 包围盒数据不知道从何处获取
    //坐标
    bullet->setPosition(birthPos);
    //加入子弹list
    return true;
}