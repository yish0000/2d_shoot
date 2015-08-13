/*
* ------------------------------------------------------------------------
*  Name:   SCHostPlayerController.cpp
*  Desc:   ���controller
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
#include "Utility/SCUtilityFunc.h"
#include "Game/SCWorld.h"

USING_NS_CC;

int SCHostPlayerController::MessageHandler(const Message &msg)
{
    //�˴�����msg���ַ�����Ӧ���������
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

	Point bulletPos;
	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getObject()->getComponent(SC_COMPONENT_ARMATURE));
	if( pArmature )
	{
		Point vBulletPos;
		cocostudio::Bone* pBone = pArmature->getArmature()->getBone("qiangkou");
		if (pBone)
		{
			vBulletPos = pBone->convertToWorldSpace(Point(0, 0));
		}
		else
		{
			vBulletPos = getObject()->getPosition();
			if (getObject()->getFaceDirection() > 0)
				vBulletPos += Point(80, 40);
			else
				vBulletPos += Point(-80, 40);
		}

		glb_getWorld()->GenerateBullet(1, vBulletPos);
	}
}
