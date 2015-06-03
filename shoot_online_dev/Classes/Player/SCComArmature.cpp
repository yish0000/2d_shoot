/*
 * ------------------------------------------------------------------------
 *  Name:   SCComArmature.cpp
 *  Desc:   骨骼动画组件
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCHostPlayer.h"
#include "SCComArmature.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

SCComArmature::SCComArmature(SCObject* pObj, const std::string& res_name)
	: SCComponentBase(pObj), m_sResName(res_name), m_pArmature(NULL), m_pAnimation(NULL)
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
	return true;
}

void SCComArmature::update(float dt)
{
}