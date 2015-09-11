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
#include "Data/SCDataTypes.h"

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
    SCHostPlayer(int tid);
	virtual ~SCHostPlayer();

	static SCHostPlayer* create(int tid);

	virtual bool init();
	virtual void update(float dt);

    virtual int DispatchMessage(const Message& msg);

	SCHostPlayerController* GetController() { return _controller; }
	SCHostPlayerDispatcher* GetDispatcher() { return _dispatcher; }

	int getCurHP();
	int getMaxHP();

	cocos2d::Rect getBoundingBox();

	const PLAYER_ESSENCE* getEssence() const { return m_pEssence; }

protected:
	PLAYER_ESSENCE* m_pEssence;
    SCHostPlayerController* _controller;
    SCHostPlayerDispatcher* _dispatcher;
};

#endif
