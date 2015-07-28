/*
* ------------------------------------------------------------------------
*  Name:   SCHostPlayerController.cpp
*  Desc:   玩家controller
*  Author: umiringo
*  Date:   2015/7/1
* ------------------------------------------------------------------------
*/

#include "SCHostPlayerController.h"
#include "common/message.h"
#include "Components/SCComponentBase.h"
#include "Components/SCComProperty.h"
#include "Components/SCComPlayerMove.h"
#include "Components/SCComArmature.h"
#include "Components/SCComPlayerFSM.h"

USING_NS_CC;

int SCHostPlayerController::MessageHandler(const Message &msg)
{
    //此处解析msg，分发给相应的组件处理
    switch (msg.type)
    {
    case MSG_ATTACK:
        CCASSERT(msg.pack_length >= sizeof(attack_msg), "MSG_ATTACK length not fit!");
        attack_msg atk_msg = *(attack_msg*)msg.pack;
        SCComProperty *pCom = dynamic_cast<SCComProperty *>(getObject()->getComponent(SC_COMPONENT_PROPERTY));
        if (!pCom)
        {
            CCLOG("SCHostPlayerController Component not found ! msg type : %d", msg.type);
            return 0;
        }
        pCom->HandleAttackMsg(atk_msg);
        break;
    }
    return 0;
}

void SCHostPlayerController::Move(float xDir, float yDir)
{
    SCComPlayerMove* pPlayerMove = dynamic_cast<SCComPlayerMove*>(getObject()->getComponent(SC_COMPONENT_PLAYERMOVE));
    pPlayerMove->move(xDir, yDir);

    if (xDir < 0.0f)
        getObject()->setFaceDirection(-1);
    else if (xDir > 0.0f)
        getObject()->setFaceDirection(1);
}

void SCHostPlayerController::Jump()
{
    SCComPlayerMove* pPlayerMove = dynamic_cast<SCComPlayerMove*>(getObject()->getComponent(SC_COMPONENT_PLAYERMOVE));
    pPlayerMove->jump();
}

void SCHostPlayerController::Attack()
{
	SCComPlayerFSM* pPlayerFSM = dynamic_cast<SCComPlayerFSM*>(getObject()->getComponent(SC_COMPONENT_PLAYERFSM));
	pPlayerFSM->doAttack();
}
