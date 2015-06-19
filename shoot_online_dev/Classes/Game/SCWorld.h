#ifndef __LOGIC_SCWORLD_H__
#define __LOGIC_SCWORLD_H__

#include "ObjectManager.h"
#include "MessageQueue.h"
#include <vector>
#include "SCobject.h"
#include "SCNpc.h"
#include "Player/SCHostPlayer.h"
#include "2d/CCNode.h"
#include "SCTiledMap.h"


class SCWorld : public cocos2d::Node
{
private:
    ObjectManager<SCNpc> _npc_manager;//npc列表
    SCHostPlayer *player;
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
    
	void SendMessage(const Message& msg);
	void SendMessage(const std::vector<GID>& glist, const Message& msg);
    void DispatchMessage(const Message& msg);
    virtual bool init();
    virtual void update(float dt);
};

#endif //__LOGIC_SCWORLD_H__