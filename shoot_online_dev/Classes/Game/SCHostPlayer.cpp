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
    delete _controller;
    _controller = NULL;
    delete _dispatcher;
    _dispatcher = NULL;
}

int SCHostPlayer::DispatchMessage(const Message &msg)
{
    return 0;
}

bool SCHostPlayer::init()
{
	if( !SCObject::init() )
		return false;

    _controller = new SCHostPlayerController();
    _dispatcher = new SCHostPlayerDispatcher();
	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getComponent(SC_COMPONENT_ARMATURE));
	pArmature->playAnimation("zhanli", true);
	return true;
}



