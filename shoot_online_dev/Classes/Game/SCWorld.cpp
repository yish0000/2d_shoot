//
//  world.cpp
//  ShootOnline
//
//  Created by 琰 陈 on 15/6/18.
//
//

#include <stdio.h>
#include "SCWorld.h"

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
SCWorld::SCWorld()
{
    _msg_queue = new MessageQueueList(this);
}

SCWorld::~SCWorld()
{
}

bool SCWorld::init()
{
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
    _msg_queue->update(dt);
    _npc_manager.update(dt);
}

