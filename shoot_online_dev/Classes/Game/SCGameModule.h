/*
 * ------------------------------------------------------------------------
 *  Name:   SCGameModule.h
 *  Desc:   ÓÎÏ·Âß¼­Ä£¿é
 *  Author: Yish
 *  Date:   2015/6/24
 * ------------------------------------------------------------------------
 */

#ifndef __SC_GAMEMODULE_H__
#define __SC_GAMEMODULE_H__

#include "Module/SCModuleBase.h"
#include "SCWorld.h"

class SCGameModule : public SCModuleBase
{
public:
	SCGameModule();
	virtual ~SCGameModule();

	virtual bool init();
	virtual void update(float dt);

	SCWorld* getWorld() { return m_pWorld; }

protected:
	SCWorld* m_pWorld;

protected:
	void initEventHandlers();

	// Event handlers
	void onEventSwitchGameState(SCEvent* pEvent);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_GAMEMODULE_H__