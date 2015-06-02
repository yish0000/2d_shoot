/*
 * ------------------------------------------------------------------------
 *  Name:   SCGeometry.h
 *  Desc:   һЩ������ײ��صĺ���
 *  Author: Yish
 *  Date:   2015/6/1
 * ------------------------------------------------------------------------
 */

#ifndef __SC_GEOMETRY_H__
#define __SC_GEOMETRY_H__

#include "base/ccTypes.h"

class SCGeometry
{
public:

	// ���������Χ�е���ײ
	static bool bbIntersects(const cocos2d::Rect& a, const cocos2d::Rect& b);
	
	// ���������Χ���ཻ����
	static cocos2d::Rect getIntersectsRect(const cocos2d::Rect& a, const cocos2d::Rect& b);
};

#endif	//#ifndef __SC_GEOMETRY_H__