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
#include "Components/SCComPlayerProperty.h"
#include "Components/SCComPlayerMove.h"
#include "Components/SCComArmature.h"
#include "Components/SCComPlayerFSM.h"
#include "Utility/SCUtilityFunc.h"
#include "Game/SCWorld.h"
#include "Game/SCGameJoystick.h"
#include "Scene/SCSceneBattle.h"

USING_NS_CC;

int SCHostPlayerController::MessageHandler(const Message &msg)
{

    //此处解析msg，分发给相应的组件处理
    switch (msg.type)
    {
    case MSG_ATTACK:
        CCASSERT(msg.pack_length >= sizeof(attack_msg), "MSG_ATTACK length not fit!");
        attack_msg atk_msg = *(attack_msg*)msg.pack;
        SCComPlayerProperty *pCom = dynamic_cast<SCComPlayerProperty *>(getObject()->getComponent(SC_COMPONENT_PLAYER_PROPERTY));
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
    if (!getObject()->isActive())
        return;
    SCComPlayerMove* pPlayerMove = dynamic_cast<SCComPlayerMove*>(getObject()->getComponent(SC_COMPONENT_PLAYERMOVE));
    pPlayerMove->move(xDir, yDir);

    if (xDir < 0.0f)
        getObject()->setFaceDirection(-1);
    else if (xDir > 0.0f)
        getObject()->setFaceDirection(1);
}

void SCHostPlayerController::Jump()
{
    if (!getObject()->isActive())
        return;
	SCSceneBattle* pScene = dynamic_cast<SCSceneBattle*>(glb_getCurScene());
	if (!pScene) return;
	SCGameJoystick* pJoystick = pScene->getJoystick();
	if (!pJoystick) return;

	SCComPlayerMove* pPlayerMove = dynamic_cast<SCComPlayerMove*>(getObject()->getComponent(SC_COMPONENT_PLAYERMOVE));
	pPlayerMove->jump(pJoystick->getYDir() < -0.5f);
}

void SCHostPlayerController::Attack()
{
    if (!getObject()->isActive())
        return;
	SCComPlayerFSM* pPlayerFSM = dynamic_cast<SCComPlayerFSM*>(getObject()->getComponent(SC_COMPONENT_PLAYERFSM));
	pPlayerFSM->doAttack();

	Point bulletPos;
	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getObject()->getComponent(SC_COMPONENT_ARMATURE));
	if( pArmature )
	{
		Point vBulletPos;
		if (!pArmature->getBoneWorldPos("qiang", vBulletPos))
		{
			vBulletPos = getObject()->getPosition();
			if (getObject()->getFaceDirection() > 0)
				vBulletPos += Point(80, 40);
			else
				vBulletPos += Point(-80, 40);
		}

        glb_getWorld()->GenerateBullet(1, vBulletPos, getObject());
	}
}
