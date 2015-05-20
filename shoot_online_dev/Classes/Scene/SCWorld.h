/*
 * ------------------------------------------------------------------------
 *  Name:   SCWorld.h
 *  Desc:   世界对象
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#ifndef __SC_WORLD_H__
#define __SC_WORLD_H__

#include "2d/CCNode.h"

class SCWorld : public cocos2d::Node
{
public:
	SCWorld();
	virtual ~SCWorld();

	virtual void onEnterTransitionDidFinish();
	virtual void onExit();


};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_WORLD_H__