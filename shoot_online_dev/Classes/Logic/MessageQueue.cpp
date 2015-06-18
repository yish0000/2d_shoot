/*
* ------------------------------------------------------------------------
*  Name:  	MessageQueue.cpp
*  Desc:   单线程消息队列
*  Author: umiringo
*  Date:   2015/6/1
* ------------------------------------------------------------------------
*/


#include "MessageQueue.h"
#include "world.h"

/*
	MessageQueue::GIDMultiCast
*/

void MessageQueue::GIDMultiCast::Send()
{
	//先扫描
	for(auto v : gid_list){
		if(!v.IsValid()){
			continue;
		}	
		msg->dest = v;
        World::GetInstance()->DispatchMessage(msg);
	}
}

/*
	MessageQueue
*/

void MessageQueue::Send()
{
	for(auto v : _queue){
        World::GetInstance()->DispatchMessage(*v);
	}
	for(auto v : _gid_muilti_queue){
		v->Send();
	}
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