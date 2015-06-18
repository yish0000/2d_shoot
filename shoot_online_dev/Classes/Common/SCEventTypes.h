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

#define SC_EVENT_MODULE_INITED "module_inited"
#define SC_EVENT_NEW_PROTOCOL "new_protocol"

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

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_EVENTTYPES_H__