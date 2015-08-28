#ifndef __LOGIC_SCWORLD_H__
#define __LOGIC_SCWORLD_H__

#include "2d/CCNode.h"

#include "ObjectManager.h"
#include "MessageQueue.h"
#include "Data/SCDataTypes.h"
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
	int m_iWorldID;
	WORLD_ESSENCE* m_pEssence;		// 模板数据
    ObjectManager<SCNpc> _npc_manager;//npc列表
    ObjectManager<SCBullet> _bullet_manager; //子弹列表

    SCHostPlayer *m_pHostPlayer;
	MessageQueueList *_msg_queue;
    SCTiledMap* m_pTileMap;

    int64_t npcOriginID;
    int64_t bulletOriginID;

public:
    SCWorld(int tid);
    virtual ~SCWorld();

	static SCWorld* create(int worldId);

	virtual bool init();
	virtual void update(float dt);

	// 获取模板数据
	const WORLD_ESSENCE* getEssence() const { return m_pEssence; }

private:
    SCNpc* FindNPCByID(int64_t id);
    SCObject* FindObjectByMsg(const Message& msg);

public:
    bool GenerateNpc(int tid, const cocos2d::Point& birthPos);
    bool GenerateBullet(int tid, const cocos2d::Point& birthPos,SCObject* owner);
    SCTiledMap* getTileMap() { return m_pTileMap; }
	SCHostPlayer* getHostPlayer() { return m_pHostPlayer; }

	bool checkCollision(const cocos2d::Rect& bb, const cocos2d::Point& oldPos,
		const cocos2d::Point& newPos, CollisionResult& result);

	// 获取碰撞到的NPC
	bool checkNPCCollision(const cocos2d::Rect& bb, const cocos2d::Point& oldPos,
		const cocos2d::Point& newPos, std::vector<int64_t>& npcList);
    bool checkPlayerCollision(const cocos2d::Rect& bb, const cocos2d::Point& oldPos,
        const cocos2d::Point& newPos);

	void sendMessage(const Message& msg);
	void sendMessage(const std::vector<GID>& glist, const Message& msg);
    void dispatchMessage(const Message& msg);
    void RemoveNPC(SCNpc *pNpc);

    
};

#endif //__LOGIC_SCWORLD_H__