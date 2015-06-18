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

#include "SCObject.h"

/** 主玩家的动画列表
gongji
benpao
zhanli
tiaoyue-up
tiaoyue-xunhuan
tiaoyue-down
siwang
*/
class SCHostPlayer : public SCObject
{
public:
    SCHostPlayer();
	virtual ~SCHostPlayer();

	virtual bool init();

	void move(float xDir, float yDir);
	void jump();
	void attack();
    
    virtual int DispatchMessage(const Message& msg);
protected:

};

#endif
