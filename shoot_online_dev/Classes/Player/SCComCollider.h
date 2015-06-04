/*
 * ------------------------------------------------------------------------
 *  Name:   SCComCollider.h
 *  Desc:   碰撞检测组件
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COMCOLLIDER_H__
#define __SC_COMCOLLIDER_H__

#include "base/ccTypes.h"
#include "SCComponentBase.h"

class SCComCollider : public SCComponentBase
{
public:
	SCComCollider(const cocos2d::Rect& rcBound);
	virtual ~SCComCollider();

	virtual bool init();
	virtual void update(float dt);

	void refreshBoundingBox();
	void setBoundingBox(const cocos2d::Rect& rcBound);

	const cocos2d::Rect& getBoundingBox();
	const cocos2d::Rect& getSymmetryBoundingBox();

protected:
	cocos2d::Rect m_bound;
	cocos2d::Rect m_backup;
	cocos2d::Rect m_symmetryBoundingBox;
	float m_fSymmetryHalfWidth;
	cocos2d::Point m_bbOffset;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMCOLLIDER_H__