/*
 * ------------------------------------------------------------------------
 *  Name:   SCGeometry.h
 *  Desc:   一些几何碰撞相关的函数
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

	// 检测两个包围盒的碰撞
	static bool bbIntersects(const cocos2d::Rect& a, const cocos2d::Rect& b);
	
	// 获得两个包围盒相交区域
	static cocos2d::Rect getIntersectsRect(const cocos2d::Rect& a, const cocos2d::Rect& b);
};

#endif	//#ifndef __SC_GEOMETRY_H__