/*
 * ------------------------------------------------------------------------
 *  Name:   SCModuleBase.h
 *  Desc:   Ä£¿é»ùÀà
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#ifndef __SC_MODULEBASE_H__
#define __SC_MODULEBASE_H__

#include "Common/SCEvent.h"
#include "Common/SCEventTypes.h"
#include "SCModuleTypes.h"

class SCModuleBase : public SCEventListener, public SCEventDispatcher
{
public:
	SCModuleBase();
	virtual ~SCModuleBase();

	virtual bool init();
	virtual void update(float dt);

	int getModuleType() const { return m_iType; }
	float getUpdateInterval() const { return m_fUpdateInterval; }

protected:
	int m_iType;
	float m_fUpdateInterval;

	virtual void onEventModuleInited(SCEvent* pEvent);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_MODULEBASE_H__