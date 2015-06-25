//
//  SCHostPlayer.cpp
//  ShootOnline
//
//  Created by Yish on 15/6/2.
//
//

#include "cocos2d.h"
#include "SCHostPlayer.h"
#include "Components/SCComArmature.h"
#include "Components/SCComCollider.h"
#include "Components/SCComPlayerFSM.h"
#include "Components/SCComPlayerMove.h"

USING_NS_CC;

SCHostPlayer::SCHostPlayer() : SCObject()
{
	Rect rcBound(-32, 0, 64, 128);
	addComponent(SC_COMPONENT_ARMATURE, (void*)"nanzhujue");
	addComponent(SC_COMPONENT_COLLIDER, (void*)&rcBound);
	addComponent(SC_COMPONENT_PLAYERFSM, NULL);
	addComponent(SC_COMPONENT_PLAYERMOVE, NULL);
}

SCHostPlayer::~SCHostPlayer()
{
}

int SCHostPlayer::DispatchMessage(const Message &msg)
{
    return 0;
}

bool SCHostPlayer::init()
{
	if( !SCObject::init() )
		return false;

	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getComponent(SC_COMPONENT_ARMATURE));
	pArmature->playAnimation("zhanli", true);
	return true;
}

void SCHostPlayer::move(float xDir, float yDir)
{
	SCComPlayerMove* pPlayerMove = dynamic_cast<SCComPlayerMove*>(getComponent(SC_COMPONENT_PLAYERMOVE));
	pPlayerMove->move(xDir, yDir);

	if( xDir < 0.0f )
		setFaceDirection(-1);
	else if( xDir > 0.0f )
		setFaceDirection(1);
}

void SCHostPlayer::jump()
{
	SCComPlayerMove* pPlayerMove = dynamic_cast<SCComPlayerMove*>(getComponent(SC_COMPONENT_PLAYERMOVE));
	pPlayerMove->jump();
}

void SCHostPlayer::attack()
{
	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getComponent(SC_COMPONENT_ARMATURE));
	pArmature->playAnimation("gongji", false);
}