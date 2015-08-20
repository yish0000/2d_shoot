/*
 * ------------------------------------------------------------------------
 *  Name:   SCGameModule.cpp
 *  Desc:   ÓÎÏ·Âß¼­Ä£¿é
 *  Author: Yish
 *  Date:   2015/6/24
 * ------------------------------------------------------------------------
 */

#include "SCGameModule.h"
#include "Scene/SCSceneManager.h"
#include "Scene/SCSceneBase.h"
#include "SCHostPlayer.h"
#include "Utility/SCUtilityFunc.h"
#include "UI/SCUIModule.h"
#include "2d/CCShapeNode.h"
#include "SCGame.h"

USING_NS_CC;

SCGameModule::SCGameModule()
	: SCModuleBase(MODULE_TYPE_GAME), m_pWorld(NULL)
{
}

SCGameModule::~SCGameModule()
{
	CC_SAFE_RELEASE(m_pWorld);
}

bool SCGameModule::init()
{
	if (!SCModuleBase::init())
		return false;

	initEventHandlers();
	return true;
}

void SCGameModule::initEventHandlers()
{
	addEventListener(SC_EVENT_SWITCH_GAMESTATE, sceventcallback_selector(SCGameModule::onEventSwitchGameState));
}

void SCGameModule::update(float dt)
{
	SCModuleBase::update(dt);

	if (m_pWorld)
		m_pWorld->update(dt);
}

void SCGameModule::onEventSwitchGameState(SCEvent* pEvent)
{
	SCEventSwitchGameState* pState = dynamic_cast<SCEventSwitchGameState*>(pEvent);
	if (pState->m_iNewState != SCGame::GS_BATTLE)
		CC_SAFE_RELEASE(m_pWorld);
	else
	{
		CCASSERT(m_pWorld == NULL, "m_pWorld is not null!");

		SCSceneBase* pCurScene = SCSceneManager::getInstance().getCurScene();
		m_pWorld = SCWorld::create(101);
		if (!m_pWorld)
		{
			CCLOG("SCGameModule::init, create the world (%d) failed!", 101);
		}
		else
		{
			m_pWorld->retain();
			pCurScene->addChild(m_pWorld);
		}
	}
}