//
//  SCSceneBattle.cpp
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#include "SCSceneBattle.h"
#include "Game/SCGameJoystick.h"
#include "cocos2d.h"
#include "Utility/SCUtilityFunc.h"
#include "Player/SCHostPlayer.h"

USING_NS_CC;

SCSceneBattle::SCSceneBattle()
    : SCSceneBase("Battle"), m_pJoystick(NULL)
{
}

bool SCSceneBattle::init()
{
    if( !SCSceneBase::init() )
        return false;
    
    m_pJoystick = SCGameJoystick::create();
    addChild(m_pJoystick, 1000);

	// 加一个跳的按钮
	MenuItem* pBtnJump = MenuItemSprite::create(
		Sprite::create("ui/joystick/jump1.png"), Sprite::create("ui/joystick/jump2.png"), NULL,
		CC_CALLBACK_1(SCSceneBattle::onBtnJump, this));
	pBtnJump->setPosition(900, 100);

	// 攻击按钮
	MenuItem* pBtnAttack = MenuItemSprite::create(
		Sprite::create("ui/joystick/attack1.png"), Sprite::create("ui/joystick/attack2.png"), NULL,
		CC_CALLBACK_1(SCSceneBattle::onBtnAttack, this));
	pBtnAttack->setPosition(800, 100);

	Menu* pMenu = Menu::create(pBtnJump, pBtnAttack, NULL);
	pMenu->setPosition(Vec2::ZERO);
	addChild(pMenu, 1000);
    return true;
}

void SCSceneBattle::onBtnJump(cocos2d::Ref* pSender)
{
	SCHostPlayer* pHost = glb_getHostPlayer();
	pHost->jump();
}

void SCSceneBattle::onBtnAttack(cocos2d::Ref* pSender)
{
	SCHostPlayer* pHost = glb_getHostPlayer();
	pHost->attack();
}