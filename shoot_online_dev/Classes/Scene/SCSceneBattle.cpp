//
//  SCSceneBattle.cpp
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#include "cocos2d.h"
#include "SCSceneBattle.h"
#include "Game/SCGameJoystick.h"
#include "Game/SCHostPlayer.h"
#include "Scene/SCTiledMap.h"
#include "Utility/SCUtilityFunc.h"

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

//     Size winSize = Director::getInstance()->getWinSize();
//     
// 	// 加一个跳的按钮
// 	MenuItem* pBtnJump = MenuItemSprite::create(
// 		Sprite::create("ui/joystick/jump1.png"), Sprite::create("ui/joystick/jump2.png"), NULL,
// 		CC_CALLBACK_1(SCSceneBattle::onBtnJump, this));
// 	pBtnJump->setPosition(winSize.width - 60, 100);
// 
// 	// 攻击按钮
// 	MenuItem* pBtnAttack = MenuItemSprite::create(
// 		Sprite::create("ui/joystick/attack1.png"), Sprite::create("ui/joystick/attack2.png"), NULL,
// 		CC_CALLBACK_1(SCSceneBattle::onBtnAttack, this));
// 	pBtnAttack->setPosition(winSize.width - 160, 100);
// 
// 	Menu* pMenu = Menu::create(pBtnJump, pBtnAttack, NULL);
// 	pMenu->setPosition(Vec2::ZERO);
// 	addChild(pMenu, 1000);
    return true;
}

void SCSceneBattle::onBtnJump(cocos2d::Ref* pSender)
{
	SCHostPlayer* pHost = glb_getHostPlayer();
	pHost->GetController()->Jump();
}

void SCSceneBattle::onBtnAttack(cocos2d::Ref* pSender)
{
	SCHostPlayer* pHost = glb_getHostPlayer();
	pHost->GetController()->Attack();
}