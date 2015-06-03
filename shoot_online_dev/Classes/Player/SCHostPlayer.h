/*
 * ------------------------------------------------------------------------
 *  Name:   SCHostPlayer.h
 *  Desc:   主玩家对象
 *  Author: Yish
 *  Date:   2015/6/2
 * ------------------------------------------------------------------------
 */

#ifndef __SC_HOSTPLAYER_H__
#define __SC_HOSTPLAYER_H__

#include "2d/CCNode.h"

/** 游戏内的对象
*/
class SCObject : public cocos2d::Node
{
};

class SCHostPlayer : public SCObject
{
public:
    SCHostPlayer();
	virtual ~SCHostPlayer();

	virtual bool init();

protected:

};

#endif
