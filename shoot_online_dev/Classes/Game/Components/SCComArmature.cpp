﻿/*
 * ------------------------------------------------------------------------
 *  Name:   SCComArmature.cpp
 *  Desc:   骨骼动画组件
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCComArmature.h"
#include "../SCObject.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

SCComArmature::SCComArmature(const std::string& res_name)
	: SCComponentBase(SC_COMPONENT_ARMATURE), m_sResName(res_name), m_pArmature(NULL), m_pAnimation(NULL)
	, m_iInitFaceDir(1)
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
	if (!m_sRestoreAnim.empty())
	{
		if (m_pAnimation->isComplete())
		{
			m_pAnimation->play(m_sRestoreAnim);
			m_sRestoreAnim = "";
		}
	}
}

void SCComArmature::setInitFaceDir(int dir)
{
	m_iInitFaceDir = dir;
	m_pArmature->setScaleX(m_iInitFaceDir);
}

void SCComArmature::refreshArmature()
{
	int dir = m_pGameObj->getFaceDirection() * m_iInitFaceDir;
	CCASSERT(dir == 1 || dir == -1, "Invalid face direction value!!");

	m_pArmature->setScaleX(fabs(m_pArmature->getScaleX()) * dir);
}

void SCComArmature::setScale(float x, float y)
{
	m_pArmature->setScale(x, y);
}

void SCComArmature::setScale(float scale)
{
	m_pArmature->setScale(scale, scale);
}

void SCComArmature::setScaleX(float x)
{
	m_pArmature->setScaleX(x);
}

void SCComArmature::setScaleY(float y)
{
	m_pArmature->setScaleY(y);
}

void SCComArmature::playAnimation(const char* name, bool bLoop, bool bRestart, const std::string& restoreAnim)
{
	if (!bRestart)
	{
		if (m_pAnimation->getCurrentMovementID() == name)
			return;
	}

	if( !m_pAnimation->getAnimationData()->getMovement(name) )
	{
		CCLOG("SCComArmature::playAnimation, cannot find the specified animation! (%s)", name);
		return;
	}

	if( bLoop )
		m_pAnimation->play(name, -1);
	else
		m_pAnimation->play(name, -1, 0);

	m_sRestoreAnim = restoreAnim;
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

bool SCComArmature::isCurAnimComplete() const
{
	return m_pAnimation->isComplete();
}

bool SCComArmature::getBoneWorldPos(const char* name, cocos2d::Point& pos)
{
	Bone* pBone = m_pArmature->getBone(name);
	if (pBone)
	{
		Mat4 matArmature = m_pArmature->getNodeToWorldTransform();
		Mat4 matTransform = pBone->getNodeToArmatureTransform();
		Mat4 matFinal = TransformConcat(matArmature, matTransform);

		Vec3 vec3(0, 0, 0);
		Vec3 ret;
		matFinal.transformPoint(vec3, &ret);
		pos.x = ret.x;
		pos.y = ret.y;
		pos = m_pGameObj->getParent()->convertToNodeSpace(pos);
		return true;
	}

	return false;
}