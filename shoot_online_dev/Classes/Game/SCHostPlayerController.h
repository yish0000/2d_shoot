/*
* ------------------------------------------------------------------------
*  Name:   SCHostPlayerController.h
*  Desc:   ���controller
*  Author: umiringo
*  Date:   2015/7/1
* ------------------------------------------------------------------------
*/

#ifndef __SCHOSTPLAYERCONTROLLER_H__
#define __SCHOSTPLAYERCONTROLLER_H__

#include <stdio.h>
#include "Game/common/mvc.h"

class SCHostPlayer;

class SCHostPlayerController : public Controller
{
public:
    SCHostPlayerController(SCObject* pObj) : Controller(pObj) {}
    virtual ~SCHostPlayerController() {}

	virtual int MessageHandler(const Message& msg);

public: //���ⲿֱ�ӵ��õĺ���
    void Move(float xDir, float yDir);
    void Jump();
    void AttackOnce();
	void AttackBegin();
	void AttackEnd();

protected:
	void onMsgAttackOnce(const Message& msg);
};

#endif //__SCHOSTPLAYERCONTROLLER_H__
