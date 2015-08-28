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
#include "Components/SCComPlayerProperty.h"

USING_NS_CC;

SCHostPlayer::SCHostPlayer() : SCObject(GID(SC_OBJECT_HOSTPLAYER, 0), 1)
{
	_controller = new SCHostPlayerController(this);
	_dispatcher = new SCHostPlayerDispatcher(this);
}

SCHostPlayer::~SCHostPlayer()
{
	CC_SAFE_DELETE(_controller);
	CC_SAFE_DELETE(_dispatcher);
}

int SCHostPlayer::DispatchMessage(const Message &msg)
{
    return _controller->MessageHandler(msg);
}

bool SCHostPlayer::init()
{
	if( !SCObject::init() )
		return false;

	// 初始化组件
	Rect rcBound(-32, 0, 64, 128);
	addComponent(SC_COMPONENT_ARMATURE, (void*)"zhujuenan");
	addComponent(SC_COMPONENT_COLLIDER, (void*)&rcBound);
	addComponent(SC_COMPONENT_PLAYERFSM, NULL);
	addComponent(SC_COMPONENT_PLAYERMOVE, NULL);

    //测试用代码，实际应该从存档中读取数据
    scComPlayerPropertyData propertyData;
    propertyData.name = "test";
    propertyData.max_hp = 500;
    addComponent(SC_COMPONENT_PLAYER_PROPERTY, (void*)&propertyData);

	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getComponent(SC_COMPONENT_ARMATURE));
	pArmature->playAnimation("zhanli", true);
	pArmature->setInitFaceDir(-1);
	return true;
}

void SCHostPlayer::update(float dt)
{
	SCObject::update(dt);

}

cocos2d::Rect SCHostPlayer::getBoundingBox()
{
    SCComCollider* pCollider = dynamic_cast<SCComCollider*>(getComponent(SC_COMPONENT_COLLIDER));
    if (pCollider)
        return pCollider->getBoundingBox();
    else
    {
        CCASSERT(0, "Cannot find the collider component!");
        return Rect(0, 0, 0, 0);
    }
}