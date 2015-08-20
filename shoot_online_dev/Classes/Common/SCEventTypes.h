/*
 * ------------------------------------------------------------------------
 *  Name:   SCEventTypes.h
 *  Desc:   事件类型
 *  Author: Yish
 *  Date:   2015/5/22
 * ------------------------------------------------------------------------
 */

#ifndef __SC_EVENTTYPES_H__
#define __SC_EVENTTYPES_H__

#include "SCEvent.h"
#include "Network/netlib/protocol/Protocol.h"

///////////////////////////////////////////////////////////////////////////
//  
//  Event types
//  
///////////////////////////////////////////////////////////////////////////

#define SC_EVENT_MODULE_INITED "sc_event_module_inited"
#define SC_EVENT_APP_ENTERBACK "sc_event_app_enterback"
#define SC_EVENT_APP_ENTERFRONT "sc_event_app_enterfront"
#define SC_EVENT_NEW_PROTOCOL "sc_event_new_protocol"
#define SC_EVENT_SWITCH_GAMESTATE "sc_event_switch_gamestate"

///////////////////////////////////////////////////////////////////////////
//  
//  Event structures
//  
///////////////////////////////////////////////////////////////////////////

class SCEventNewProtocol : public SCEvent
{
public:
	SCEventNewProtocol(const scnet::Protocol* p) : SCEvent(SC_EVENT_NEW_PROTOCOL), m_pProtocol(p) {}
	~SCEventNewProtocol() { if( m_pProtocol ) delete m_pProtocol; }

	const scnet::Protocol* getProtocol() { return m_pProtocol; }

protected:
	const scnet::Protocol* m_pProtocol;
};

class SCEventSwitchGameState : public SCEvent
{
public:
	SCEventSwitchGameState(int oldState, int newState)
		: SCEvent(SC_EVENT_SWITCH_GAMESTATE), m_iOldState(oldState), m_iNewState(newState) {}

public:
	int m_iOldState, m_iNewState;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_EVENTTYPES_H__