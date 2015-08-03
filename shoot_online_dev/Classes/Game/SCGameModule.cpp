/*
 * ------------------------------------------------------------------------
 *  Name:   SCGameModule.cpp
 *  Desc:   ��Ϸ�߼�ģ��
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

USING_NS_CC;

SCGameModule::SCGameModule()
	: SCModuleBase(MODULE_TYPE_GAME), m_pWorld(NULL)
{
}

SCGameModule::~SCGameModule()
{
}

bool SCGameModule::init()
{
	if (!SCModuleBase::init())
		return false;

	SCSceneManager::getInstance().enterScene(SCENE_BATTLE, TRANS_FADEIN, 0.4f);

	SCSceneBase* pCurScene = SCSceneManager::getInstance().getCurScene();
	m_pWorld = SCWorld::create(101);
	if (!m_pWorld)
	{
		CCLOG("SCGameModule::init, create the world (%d) failed!", 101);
		return false;
	}

	pCurScene->addChild(m_pWorld);
	return true;
}

void SCGameModule::update(float dt)
{
	SCModuleBase::update(dt);

	if (m_pWorld)
		m_pWorld->update(dt);
}