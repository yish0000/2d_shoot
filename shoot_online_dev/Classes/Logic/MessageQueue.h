#ifndef __LOGIC_MESSAGEQUEUE_H__
#define __LOGIC_MESSAGEQUEUE_H__

/*
* ------------------------------------------------------------------------
*  Name:   MessageQueue.h
*  Desc:   单线程消息队列
*  Author: umiringo
*  Date:   2015/6/1
* ------------------------------------------------------------------------
*/

#include <vector>
#include <Logic/common/type.h>
#include <Logic/common/message.h>
#include <Common/SCThread.h>
#include "config.h"


//消息队列
class MessageQueue
{
	typedef std::vector<GID> GIDLIST; //用于广播
	class GIDMultiCast //广播消息体类
	{
	public:
		GIDLIST gid_list;
		Message *msg;

		GIDMultiCast(GIDLIST &list, const Message& msg) : msg(Message::DuplicateMessage(msg))
		{
			gid_list.swap(list);
		}

		~GIDMultiCast()
		{
			Message::FreeMessage(msg);
		}

	public:
		void Send();
	};

	typedef std::vector<Message*> MSGQUEUE;
	typedef std::vector<GIDMultiCast*> GIDMULTICASTQUEUE;

	MSGQUEUE _queue;
 	GIDMULTICASTQUEUE _gid_muilti_queue;

public:
 	MessageQueue() {}
 	~MessageQueue() {}

private:
 	template<class T>
 	inline void clear_ptr_vector(std::vector<T>& vec)
 	{
 		for(size_t i = 0; i < vec.size(); i++){
 			delete vec[i];
 		}
 		vec.clear();
 	}

public:
 	void Swap(MessageQueue & msgQueue)
 	{
 		_queue.swap(msgQueue._queue);
 		_gid_muilti_queue.swap(msgQueue._gid_muilti_queue);
 	}

 	void AddMessage(const Message &msg)
 	{
 		_queue.push_back(Message::DuplicateMessage(msg));
 	}

 	void AddMuiltiMessage(GIDLIST& list, const Message &msg)
 	{
 		_gid_muilti_queue.push_back(new GIDMultiCast(list, msg));
 	}

 	bool IsEmpty()
 	{
 		return _queue.empty() && _gid_muilti_queue.empty();
 	}

 	void Clear()
 	{
 		clear_ptr_vector(_queue);
 		clear_ptr_vector(_gid_muilti_queue);
 	}
 	void Send();
};

//消息队列列表
class MessageQueueList
{
 	//MessageQueue * _list[MAX_MESSAGE_CACHE];
 	MessageQueue _cur_queue;
 	size_t _cur_queue_count;
 	SCMutex _lock;
 	enum{
 		MAX_MESSAGE_SIZE = 256,
    };
public:
    MessageQueueList():_cur_queue_count(0)
	{
	}

	~MessageQueueList() {}

private:
 	inline void SendCurQueue()
 	{
 		MessageQueue *pQueue = new MessageQueue();
 		_cur_queue.Swap(*pQueue);
 		pQueue->Send();
 		_cur_queue_count = 0;
 	}

 	inline void TrySendCurQueue()
 	{
 		if(++_cur_queue_count < MAX_MESSAGE_SIZE)
 			return;
 		SendCurQueue();
 	}

public:
	void AddMessage(const Message &msg);
	void AddMuiltiMessage(std::vector<GID> list, const Message & msg);
    void update(float dt); //心跳中处理
};


#endif //__LOGIC_MESSAGEQUEUE_H__