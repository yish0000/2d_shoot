/*
 * ------------------------------------------------------------------------
 *  Name:   Event.h
 *  Desc:   �¼�ϵͳ
 *  Author: Yish
 *  Date:   2015/5/21
 * ------------------------------------------------------------------------
 */

#ifndef __SC_EVENT_H__
#define __SC_EVENT_H__

#include <string>
#include <map>
#include <functional>
#include <queue>
#include "SCThread.h"

class SCEventListener;
class SCEventDispatcher;

/** �¼�����
*/
class SCEvent
{
public:
	SCEvent(const std::string& type) : m_sType(type), m_pSource(NULL) {}
	virtual ~SCEvent() {}

	const std::string& getType() const { return m_sType; }
	SCEventDispatcher* getSource() const { return m_pSource; }

	void setSource(SCEventDispatcher* pSource) { m_pSource = pSource; }

protected:
	std::string m_sType;
	SCEventDispatcher* m_pSource;
};

/** �¼�����������
*/
class SCEventListener
{
public:
	virtual void handle(SCEvent* pEvent) {}
};

typedef void (SCEventListener::*SEL_SCEventCallback) (SCEvent* pEvent);
#define sceventcallback_selector(selector) (SEL_SCEventCallback)(&selector)

/** �¼��ɷ�
*/
class SCEventDispatcher
{
	friend class SCEventProcessQueue;

public:
	SCEventDispatcher() {}
	virtual ~SCEventDispatcher() {}

	// ���߳��ڵ���
	void addEventListener(const std::string& eventType, SCEventListener* listener, SEL_SCEventCallback callback, int priority=0);
	void removeEventListener(const std::string& eventType, SCEventListener* listener, SEL_SCEventCallback callback, int priority=0);
	void removeAllForListener(SCEventListener* listener);
	void removeAllListeners();

	void dispatchEvent(SCEvent* pEvent, bool bDeleteAfterComplete = false);
	void dispatchEvent(const std::string& type);

private:
	typedef std::multimap<SCEventListener*, SEL_SCEventCallback> ListenerMap;
	typedef std::map<int, ListenerMap, std::greater<int> > PriorityMap;
	typedef std::map<std::string, PriorityMap> EventMap;
	EventMap m_eventMap;

	// �����¼�
	void onEvent(SCEvent* pEvent, bool bDeleteAfterComplete);
};

/** �¼�����(GL Thread mainLoop��ִ�е�)
*/
class SCEventProcessQueue
{
	struct Event
	{
		SCEventDispatcher* pDispatcher;
		SCEvent* pEvent;
		bool bDeleteAfterComplete;
	};

public:
	SCEventProcessQueue();
	virtual ~SCEventProcessQueue();

	void addEvent(SCEventDispatcher* dispatcher, SCEvent* pEvent, bool bDeleteAfterComplete = false);
	void update(float dt);

	static SCEventProcessQueue& getInstance();

protected:
	bool m_bQueueEmpty;
	std::queue<Event> m_dispatchQueue;
	SCMutex m_mutexQueue;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_EVENT_H__