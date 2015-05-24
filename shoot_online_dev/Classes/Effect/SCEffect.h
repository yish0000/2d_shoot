/*
 * ------------------------------------------------------------------------
 *  Name:   SCEffect.h
 *  Desc:   特效对象
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#ifndef __SC_EFFECT_H__
#define __SC_EFFECT_H__

#include "2d/CCNode.h"

class SCEffect : public cocos2d::Node
{
public:
	SCEffect();
	virtual ~SCEffect();

	virtual bool init();
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_EFFECT_H__