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
private:
    SCHostPlayer *gameObject;
public:
    SCHostPlayerController() {}
    virtual ~SCHostPlayerController() {}
    virtual int MessageHandler(const Message& msg);

    SCHostPlayer* getObject() { return gameObject; }

public: //���ⲿֱ�ӵ��õĺ���
    void Move(float xDir, float yDir);
    void Jump();
    void Attack();

};

#endif //__SCHOSTPLAYERCONTROLLER_H__
