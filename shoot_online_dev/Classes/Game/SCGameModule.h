/*
 * ------------------------------------------------------------------------
 *  Name:   SCGameModule.h
 *  Desc:   游戏逻辑模块
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

	// 播放慢镜头
	void playTimeScaleEffect(float fTime = 1.0f, float fScale = 0.2f);
	// 恢复镜头速度到正常
	void resumeTimeScale();

	SCWorld* getWorld() { return m_pWorld; }

protected:
	SCWorld* m_pWorld;

protected:
	void initEventHandlers();

	// Event handlers
	void onEventSwitchGameState(SCEvent* pEvent);
	void onEventStageClear(SCEvent* pEvent);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_GAMEMODULE_H__