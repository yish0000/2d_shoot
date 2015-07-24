#ifndef __LOGIC_SCWORLD_H__
#define __LOGIC_SCWORLD_H__

#include "2d/CCNode.h"

#include "ObjectManager.h"
#include "MessageQueue.h"
#include "SCObject.h"
#include "SCNpc.h"
#include "SCHostPlayer.h"
#include "Scene/SCTiledMap.h"
#include "SCBullet.h"

class SCWorld : public cocos2d::Node
{
public:
	
	// 碰撞检测的结果
	struct CollisionResult
	{
		bool leftCollision;
		bool rightCollision;
		bool bottomCollision;
		bool leftBottomCollision;
		bool rightBottomCollision;

		float leftCollisionX;
		float bottomCollisionY;
		float rightCollisionX;

		CollisionResult() : leftCollision(false), rightCollision(false), bottomCollision(false),
			leftBottomCollision(false), rightBottomCollision(false), leftCollisionX(0.0f),
			bottomCollisionY(0.0f), rightCollisionX(0.0f)
		{
		}
	};

private:
    ObjectManager<SCNpc> _npc_manager;//npc列表
    ObjectManager<SCBullet> _bullet_manager; //子弹列表

    SCHostPlayer *m_pHostPlayer;
	MessageQueueList *_msg_queue;
    SCTiledMap* m_pTileMap;

    int64_t npcOriginID;
    int64_t bulletOriginID;

public:
    SCWorld();
    virtual ~SCWorld();
    CREATE_FUNC(SCWorld);

	virtual bool init();
	virtual void update(float dt);

private:
    SCNpc* FindNPCByID(int64_t id);
    SCObject* FindObjectByMsg(const Message& msg);

    bool GenerateNpc(int64_t id, cocos2d::Point birthPos);
    bool GenerateBullet(int64_t id, cocos2d::Point birthPos);

public:
    SCTiledMap* getTileMap() { return m_pTileMap; }
	SCHostPlayer* getHostPlayer() { return m_pHostPlayer; }

	bool checkCollision(const cocos2d::Rect& bb, const cocos2d::Point& oldPos,
		const cocos2d::Point& newPos, CollisionResult& result);

	void SendMessage(const Message& msg);
	void SendMessage(const std::vector<GID>& glist, const Message& msg);
    void DispatchMessage(const Message& msg);
};

#endif //__LOGIC_SCWORLD_H__