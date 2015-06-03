//
//  SCHostPlayer.cpp
//  ShootOnline
//
//  Created by Yish on 15/6/2.
//
//

#include "cocos2d.h"
#include "SCHostPlayer.h"
#include "SCComArmature.h"

USING_NS_CC;

SCHostPlayer::SCHostPlayer() : SCObject(0, 0)
{
	Rect rcBound(-32, 0, 64, 128);
	addComponent(SC_COMPONENT_ARMATURE, "nanzhujue");
	addComponent(SC_COMPONENT_COLLIDER, &rcBound);
	addComponent(SC_COMPONENT_PLAYERFSM, NULL);
	addComponent(SC_COMPONENT_PLAYERMOVE, NULL);
}

SCHostPlayer::~SCHostPlayer()
{
}

bool SCHostPlayer::init()
{
	if( !SCObject::init() )
		return false;

	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getComponent(SC_COMPONENT_ARMATURE));
	pArmature->playAnimation("zhanli", true);
	return true;
}