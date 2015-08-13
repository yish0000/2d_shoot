/*
 * ------------------------------------------------------------------------
 *  Name:   SCGeometry.cpp
 *  Desc:   一些几何相关函数
 *  Author: Yish
 *  Date:   2015/6/1
 * ------------------------------------------------------------------------
 */

#include "SCGeometry.h"
#include <algorithm>

USING_NS_CC;

// 检测两个包围盒的碰撞
bool SCGeometry::bbIntersects(const cocos2d::Rect& a, const cocos2d::Rect& b)
{
	if( a.origin.x + a.size.width < b.origin.x || b.origin.x + b.size.width < a.origin.x ||
		a.origin.y + a.size.height < b.origin.y || b.origin.y + b.size.height < a.origin.y )
		return false;
	else
		return true;
}

// 获得两个包围盒相交区域
cocos2d::Rect SCGeometry::getIntersectsRect(const cocos2d::Rect& a, const cocos2d::Rect& b)
{
	cocos2d::Rect rect;
	rect.origin.x = std::max(a.origin.x, b.origin.x);
	rect.origin.y = std::max(a.origin.y, b.origin.y);
	rect.size.width = std::min(a.origin.x + a.size.width, b.origin.x + b.size.width) - rect.origin.x;
	rect.size.height = std::min(a.origin.y + a.size.height, b.origin.y + b.size.height) - rect.origin.y;
	return rect;
}