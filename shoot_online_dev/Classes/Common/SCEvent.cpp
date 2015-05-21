/*
 * ------------------------------------------------------------------------
 *  Name:   SCEvent.cpp
 *  Desc:   �¼�ϵͳ
 *  Author: Yish
 *  Date:   2015/5/21
 * ------------------------------------------------------------------------
 */

#include "SCEvent.h"
#include "base/ccMacros.h"

///////////////////////////////////////////////////////////////////////////
//  
//  class SCEventDispatcher
//  
///////////////////////////////////////////////////////////////////////////

void SCEventDispatcher::dispatchEvent(SCEvent* pEvent, bool bDeleteAfterComplete)
{
	SCEventProcessQueue::getInstance().addEvent(this, pEvent, bDeleteAfterComplete);
}

void SCEventDispatcher::dispatchEvent(const std::string& type)
{
	SCEvent e(type);
	dispatchEvent(&e);
}

void SCEventDispatcher::addEventListener(const std::string& eventType, SCEventListener* listener, SEL_SCEventCallback callback, int priority)
{
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

void SCEventDispatcher::onEvent(SCEvent* pEvent, bool bDeleteAfterComplete)
{
	EventMap::iterator eit = m_eventMap.find(pEvent->getType());
	if( eit == m_eventMap.end() )
		return;

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
}

///////////////////////////////////////////////////////////////////////////
//  
//  SCEventProcessQueue
//  
///////////////////////////////////////////////////////////////////////////

void SCEventProcessQueue::addEvent(SCEventDispatcher* dispatcher, SCEvent* pEvent, bool bDeleteAfterComplete)
{
	SCScopedMutex keeper(m_mutexQueue);

	Event ev;
	ev.pDispatcher = dispatcher;
	ev.pEvent = pEvent;
	ev.bDeleteAfterComplete = bDeleteAfterComplete;
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
		while( !m_dispatchQueue.empty() )
		{
			Event entry = m_dispatchQueue.front();
			m_dispatchQueue.pop();
			entry.pDispatcher->onEvent(entry.pEvent, entry.bDeleteAfterComplete);
		}

		m_bQueueEmpty = true;
	}
}