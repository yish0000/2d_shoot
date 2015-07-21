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

#include <Game/SCObject.h>
#include <Game/common/message.h>
#include "SCHostPlayerController.h"
#include "SCHostPlayerDispatcher.h"


/** 主玩家的动画列表
benpao
zhanli
jiguanqiang
yidonggongji
qitiao
tiaoyuekaiqiang
xunhuan
luodi
*/
class SCHostPlayer : public SCObject
{
public:
    SCHostPlayer();
	virtual ~SCHostPlayer();

	virtual bool init();
	virtual void update(float dt);

    CREATE_FUNC(SCHostPlayer);
    virtual int DispatchMessage(const Message& msg);

	SCHostPlayerController* GetController() { return _controller; }
	SCHostPlayerDispatcher* GetDispatcher() { return _dispatcher; }

protected:
    SCHostPlayerController* _controller;
    SCHostPlayerDispatcher* _dispatcher;
};

#endif
