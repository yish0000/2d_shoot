#ifndef __LOGIC_SCWORLD_H__
#define __LOGIC_SCWORLD_H__

#include "ObjectManager.h"
#include "MessageQueue.h"
#include <vector>
#include "SCobject.h"
#include "SCNpc.h"
#include "SCHostPlayer.h"
#include "2d/CCNode.h"
#include "Scene/SCTiledMap.h"


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
    SCHostPlayer *m_player;
	MessageQueueList *_msg_queue;
    SCTiledMap* m_pTileMap;

public:
    SCWorld();
    virtual ~SCWorld();
    CREATE_FUNC(SCWorld);
    
private:
    SCNpc * FindNPCByID(int64_t id);
    SCObject* FindObjectByMsg(const Message& msg);

public:
    SCTiledMap* getTileMap() { return m_pTileMap; }
	SCHostPlayer* getHostPlayer() { return m_player; }
    
	void SendMessage(const Message& msg);
	void SendMessage(const std::vector<GID>& glist, const Message& msg);
    void DispatchMessage(const Message& msg);
    virtual bool init();
    virtual void update(float dt);

	bool checkCollision(const cocos2d::Rect& bb, const cocos2d::Point& oldPos,
		const cocos2d::Point& newPos, CollisionResult& result)
};

#endif //__LOGIC_SCWORLD_H__