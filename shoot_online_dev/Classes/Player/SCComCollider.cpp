/*
 * ------------------------------------------------------------------------
 *  Name:   SCComCollider.cpp
 *  Desc:   碰撞检测组件
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCObject.h"
#include "SCComCollider.h"

USING_NS_CC;

SCComCollider::SCComCollider(const cocos2d::Rect& rcBound)
	: SCComponentBase(SC_COMPONENT_COLLIDER), m_bound(rcBound), m_fSymmetryHalfWidth(0.0f)
{
}

SCComCollider::~SCComCollider()
{
}

bool SCComCollider::init()
{
	// 备份原始的包围盒数据
	m_backup = m_bound;

	// 当前包围盒相对于原点的偏移量
	m_bbOffset.setPoint(m_bound.origin.x, m_bound.origin.y);

	// 左右对称包围盒
	m_symmetryBoundingBox = m_bound;
	// 对称包围盒半长
	m_fSymmetryHalfWidth = m_bound.size.width + m_bbOffset.x;

	refreshBoundingBox();
	m_bActive = true;
	return true;
}

void SCComCollider::update(float dt)
{
}

void SCComCollider::refreshBoundingBox()
{
	int faceDir = m_pGameObj->getFaceDirection();
	if( faceDir < 0 )
		m_bbOffset.x = -(m_backup.origin.x + m_backup.size.width);
	else
		m_bbOffset.x = m_backup.origin.x;
	m_bbOffset.y = m_backup.origin.y;
	m_bound.size.width = m_backup.size.width;
	m_bound.size.height = m_backup.size.height;
	m_fSymmetryHalfWidth = m_backup.origin.x + m_backup.size.width;
	m_symmetryBoundingBox.size.width = 2 * m_fSymmetryHalfWidth;
	m_symmetryBoundingBox.size.height = m_bound.size.height;
}

void SCComCollider::setBoundingBox(const cocos2d::Rect& rcBound)
{
	m_backup = rcBound;
	refreshBoundingBox();
}

// 获得包围盒
const cocos2d::Rect& SCComCollider::getBoundingBox()
{
	Point pos = m_pGameObj->getPosition();
	m_bound.origin.x = pos.x + m_bbOffset.x;
	m_bound.origin.y = pos.y + m_bbOffset.y;
	return m_bound;
}

// 获得y轴对称包围盒
const cocos2d::Rect& SCComCollider::getSymmetryBoundingBox()
{
	Point pos = m_pGameObj->getPosition();
	m_symmetryBoundingBox.origin.x = pos.x - m_fSymmetryHalfWidth;
	m_symmetryBoundingBox.origin.y = pos.y + m_bbOffset.y;
	return m_symmetryBoundingBox;
}