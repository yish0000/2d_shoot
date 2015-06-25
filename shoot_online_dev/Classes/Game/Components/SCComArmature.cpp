/*
 * ------------------------------------------------------------------------
 *  Name:   SCComArmature.cpp
 *  Desc:   骨骼动画组件
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCComArmature.h"
#include "../SCHostPlayer.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

SCComArmature::SCComArmature(const std::string& res_name)
	: SCComponentBase(SC_COMPONENT_ARMATURE), m_sResName(res_name), m_pArmature(NULL), m_pAnimation(NULL)
{
}

SCComArmature::~SCComArmature()
{
}

bool SCComArmature::init()
{
	m_bActive = false;

	std::string armature = "role/" + m_sResName + "/" + m_sResName + ".ExportJson";
	std::string plist = "role/" + m_sResName + "/" + m_sResName + "0.plist";
	std::string texture = "role/" + m_sResName + "/" + m_sResName + "0.png";

	ArmatureDataManager* pManager = ArmatureDataManager::getInstance();
	pManager->addArmatureFileInfo(texture, plist, armature);

	// 创建骨骼动画
	m_pArmature = Armature::create(m_sResName);
	if( !m_pArmature )
	{
		m_bActive = false;
		CCLOG("SCComArmature::init, create the armature failed!");
		return false;
	}

	m_pAnimation = m_pArmature->getAnimation();
	m_pGameObj->addChild(m_pArmature);
	m_bActive = true;
	return true;
}

void SCComArmature::update(float dt)
{
}

void SCComArmature::refreshArmature()
{
	int dir = m_pGameObj->getFaceDirection();
	CCASSERT(dir == 1 || dir == -1, "Invalid face direction value!!");

	m_pArmature->setScaleX(dir);
}

void SCComArmature::playAnimation(const char* name, bool bLoop)
{
	if( bLoop )
		m_pAnimation->play(name, -1);
	else
		m_pAnimation->play(name, -1, 0);
}

void SCComArmature::pauseAnimation()
{
	m_pAnimation->pause();
}

void SCComArmature::resumeAnimation()
{
	m_pAnimation->resume();
}

void SCComArmature::fadeTo(int opacity, float fTime)
{
	m_pArmature->runAction(FadeTo::create(fTime, opacity));
}

std::string SCComArmature::getCurAnimName() const
{
	return m_pAnimation->getCurrentMovementID();
}