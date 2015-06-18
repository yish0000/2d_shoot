#ifndef __LOGIC_SCWORLD_H__
#define __LOGIC_SCWORLD_H__

#include "ObjectManager.h"
#include "MessageQueue.h"
#include <vector>
#include "SCobject.h"
#include "SCNpc.h"
#include "Player/SCHostPlayer.h"


class SCWorld : public cocos2d::Node
{
private:
    ObjectManager<SCNpc> _npc_manager;//npc列表
    SCHostPlayer *player;
	MessageQueueList *_msg_queue;

public:
    SCWorld();
    virtual ~SCWorld();
    
private:
    SCNpc * FindNPCByID(int64_t id);
    SCObject* FindObjectByMsg(const Message& msg);
    
public:
    void Init();
	void SendMessage(const Message& msg);
	void SendMessage(const std::vector<GID>& glist, const Message& msg);
    void DispatchMessage(const Message& msg);
    virtual void update(float dt);
};

#endif //__LOGIC_SCWORLD_H__