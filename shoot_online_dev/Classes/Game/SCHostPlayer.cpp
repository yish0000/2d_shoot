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
#include "Data/SCDataModule.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;

SCHostPlayer::SCHostPlayer(int tid) : SCObject(GID(SC_OBJECT_HOSTPLAYER, 0), tid), m_pEssence(NULL)
{
	_controller = new SCHostPlayerController(this);
	_dispatcher = new SCHostPlayerDispatcher(this);
}

SCHostPlayer::~SCHostPlayer()
{
	CC_SAFE_RELEASE(m_pEssence);
	CC_SAFE_DELETE(_controller);
	CC_SAFE_DELETE(_dispatcher);
}

SCHostPlayer* SCHostPlayer::create(int tid)
{
	SCHostPlayer* pHost = new SCHostPlayer(tid);
	if (pHost && pHost->init())
		pHost->autorelease();
	else
	{
		CC_SAFE_DELETE(pHost);
	}

	return pHost;
}

int SCHostPlayer::DispatchMessage(const Message &msg)
{
    return _controller->MessageHandler(msg);
}

bool SCHostPlayer::init()
{
	if( !SCObject::init() )
		return false;

	// 获取角色模板
	m_pEssence = (PLAYER_ESSENCE*)glb_getDataModule()->getTemplate(m_tid, DT_PLAYER_ESSENCE);
	if (m_pEssence)
		m_pEssence->retain();
	else
	{
		CCLOG("SCHostPlayer::init, cannot find the specified player template(%d)!", m_tid);
		return false;
	}

	// 初始化组件
	Rect rcBound(-32, 0, 64, 128);
	addComponent(SC_COMPONENT_ARMATURE, (void*)m_pEssence->res_path.c_str());
	addComponent(SC_COMPONENT_COLLIDER, (void*)&rcBound);
	addComponent(SC_COMPONENT_PLAYERFSM, NULL);
	addComponent(SC_COMPONENT_PLAYERMOVE, NULL);
	addComponent(SC_COMPONENT_WEAPON, (void*)1);

    //测试用代码，实际应该从存档中读取数据
    scComPlayerPropertyData propertyData;
    propertyData.name = "test";
    propertyData.max_hp = m_pEssence->max_hp;
    addComponent(SC_COMPONENT_PLAYER_PROPERTY, (void*)&propertyData);

	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getComponent(SC_COMPONENT_ARMATURE));
	pArmature->playAnimation("zhanli", true);
	pArmature->setInitFaceDir(-1);

	setScale(m_pEssence->scale);
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

int SCHostPlayer::getCurHP()
{
	SCComPlayerProperty* pProp = dynamic_cast<SCComPlayerProperty*>(getComponent(SC_COMPONENT_PLAYER_PROPERTY));
	return pProp ? pProp->getCurHP() : 0;
}

int SCHostPlayer::getMaxHP()
{
	SCComPlayerProperty* pProp = dynamic_cast<SCComPlayerProperty*>(getComponent(SC_COMPONENT_PLAYER_PROPERTY));
	return pProp ? pProp->getMaxHP() : 0;
}