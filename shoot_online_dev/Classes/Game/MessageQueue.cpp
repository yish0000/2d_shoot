/*
* ------------------------------------------------------------------------
*  Name:  	MessageQueue.cpp
*  Desc:   单线程消息队列
*  Author: umiringo
*  Date:   2015/6/1
* ------------------------------------------------------------------------
*/


#include "MessageQueue.h"
#include "SCWorld.h"

/*
	MessageQueue::GIDMultiCast
*/

void MessageQueue::GIDMultiCast::Send(SCWorld *world)
{
	//先扫描
	for(auto e : gid_list){
		if(!e.IsValid()){
			continue;
		}	
		msg->dest = e;
        world->DispatchMessage(*msg);
	}
}

/*
	MessageQueue
*/

void MessageQueue::Send(SCWorld *world)
{
	for(auto e : _queue){
        world->DispatchMessage(*e);
	}
	for(auto e : _gid_muilti_queue){
        e->Send(world);
	}
    Clear();
}

/*
	MessageQueueList
*/

void MessageQueueList::AddMessage(const Message & msg)
{
	SCScopedMutex keeper(_lock);
	_cur_queue.AddMessage(msg);
	TrySendCurQueue();
}

void MessageQueueList::AddMuiltiMessage(std::vector<GID> list, const Message & msg)
{
	SCScopedMutex keeper(_lock);
	_cur_queue.AddMuiltiMessage(list, msg);
	TrySendCurQueue();
}

void MessageQueueList::update(float dt)
{
	if(_cur_queue_count > 0){
		SCScopedMutex keeper(_lock);
		if(!_cur_queue.IsEmpty())
		{
			SendCurQueue();
		}
	}
	
}