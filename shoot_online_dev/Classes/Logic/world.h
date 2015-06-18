#ifndef __LOGIC_WORLD_H__
#define __LOGIC_WORLD_H__

#include "ObjectManager.h"
#include "MessageQueue.h"

class World
{
private:
	ObjectManager<NpcObject> _npc_manager;//npc列表
	MessageQueueList _msg_queue;

public:
	World() {}
	virtual ~World() {}
	
public:
	//关于msg的接口
	void SendMessage(const Message & msg);
	void SendMessage(const std::vector<GID>& glist, const Message &msg);


};