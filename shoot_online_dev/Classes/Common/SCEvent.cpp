/*
 * ------------------------------------------------------------------------
 *  Name:   SCEvent.cpp
 *  Desc:   事件系统
 *  Author: Yish
 *  Date:   2015/5/21
 * ------------------------------------------------------------------------
 */

#include "SCEvent.h"
#include "cocos2d.h"

///////////////////////////////////////////////////////////////////////////
//  
//  class SCEventDispatcher
//  
///////////////////////////////////////////////////////////////////////////

void SCEventDispatcher::dispatchEvent(SCEvent* pEvent)
{
	SCEventProcessQueue::getInstance().addEvent(this, pEvent);
}

void SCEventDispatcher::dispatchEvent(const std::string& type)
{
	dispatchEvent(new SCEvent(type));
}

void SCEventDispatcher::addEventListener(const std::string& eventType, SCEventListener* listener, SEL_SCEventCallback callback, int priority)
{
	if( !listener || callback )
		return;

	ListenerMap& listenerMap = m_eventMap[eventType][priority];
	ListenerMap::iterator it = listenerMap.lower_bound(listener);
	ListenerMap::iterator ie = listenerMap.end();
	while( it != ie )
	{
		if( it->first != listener )
			break;
		if( it->second == callback )
			return;
		++it;
	}

	listenerMap.insert(std::make_pair(listener, callback));
}

void SCEventDispatcher::removeEventListener(const std::string& eventType, SCEventListener* listener, SEL_SCEventCallback callback, int priority)
{
	EventMap::iterator eit = m_eventMap.find(eventType);
	if( eit == m_eventMap.end() )
		return;

	PriorityMap::iterator pit = eit->second.find(priority);
	if( pit == eit->second.end() )
		return;

	ListenerMap::iterator lie = pit->second.end();
	ListenerMap::iterator lit = pit->second.lower_bound(listener);
	for(; lit != lie; ++lit)
	{
		if( lit->first != listener )
			break;

		if( lit->second == callback )
		{
			pit->second.erase(lit);

			if( pit->second.empty() )
			{
				eit->second.erase(pit);

				if( eit->second.empty() )
				{
					m_eventMap.erase(eit);
				}
			}

			break;
		}
	}
}

void SCEventDispatcher::removeAllForListener(SCEventListener* listener)
{
	EventMap::iterator eit = m_eventMap.begin(), eie = m_eventMap.end();
	while( eit != eie )
	{
		PriorityMap::iterator pit = eit->second.begin(), pie = eit->second.end();
		while( pit != pie )
		{
			if( pit->second.erase(listener) && pit->second.empty() )
			{
				eit->second.erase(pit++);
			}
			else
				++pit;
		}

		if( eit->second.empty() )
		{
			m_eventMap.erase(eit++);
		}
		else
			++eit;
	}
}

void SCEventDispatcher::removeAllListeners()
{
	m_eventMap.clear();
}

void SCEventDispatcher::onEvent(SCEvent* pEvent)
{
	CCASSERT(pEvent, "pEvent is null!");
	EventMap::iterator eit = m_eventMap.find(pEvent->getType());
	if( eit == m_eventMap.end() )
	{
		delete pEvent;
		return;
	}

	CCASSERT(!eit->second.empty(), "");
	PriorityMap backup = eit->second;
	pEvent->setSource(this);

	PriorityMap::iterator pit = backup.begin(), pie = backup.end();
	for(; pit != pie; ++pit)
	{
		ListenerMap::iterator lit = pit->second.begin(), lie = pit->second.end();
		for(; lit != lie; ++lit)
		{
			(lit->first->*lit->second)(pEvent);
		}
	}

	delete pEvent;
}

///////////////////////////////////////////////////////////////////////////
//  
//  SCEventProcessQueue
//  
///////////////////////////////////////////////////////////////////////////

SCEventProcessQueue& SCEventProcessQueue::getInstance()
{
	static SCEventProcessQueue obj;
	return obj;
}

SCEventProcessQueue::SCEventProcessQueue()
	: m_bQueueEmpty(true)
{
	cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

SCEventProcessQueue::~SCEventProcessQueue()
{
	cocos2d::Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}

void SCEventProcessQueue::addEvent(SCEventDispatcher* dispatcher, SCEvent* pEvent)
{
	SCScopedMutex keeper(m_mutexQueue);

	Event ev;
	ev.pDispatcher = dispatcher;
	ev.pEvent = pEvent;
	m_dispatchQueue.push(ev);
	m_bQueueEmpty = false;
}

void SCEventProcessQueue::update(float delta)
{
	if( m_bQueueEmpty )
		return;

	SCScopedMutex keeper(m_mutexQueue);
	if( !m_bQueueEmpty )
	{
		Event entry = m_dispatchQueue.front();
		m_dispatchQueue.pop();
		entry.pDispatcher->onEvent(entry.pEvent);

		m_bQueueEmpty = true;
	}
}