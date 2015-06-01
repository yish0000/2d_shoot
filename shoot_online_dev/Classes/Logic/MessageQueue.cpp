/*
* ------------------------------------------------------------------------
*  Name:  	MessageQueue.cpp
*  Desc:   单线程消息队列
*  Author: umiringo
*  Date:   2015/6/1
* ------------------------------------------------------------------------
*/


#include "MessageQueue.h"

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
		//TODO 发送代码填入此处
	}
}

/*
	MessageQueue
*/

void MessageQueue::Send()
{
	for(auto v : _queue){
		//TODO 发送代码填入此处
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

void MessageQueueList::update()
{
	if(_cur_queue_count > 0){
		SCScopedMutex keeper(_lock);
		if(!_cur_queue.IsEmpty())
		{
			SendCurQueue();
		}
	}
	
}