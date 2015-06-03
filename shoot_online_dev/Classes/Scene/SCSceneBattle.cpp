//
//  SCSceneBattle.cpp
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#include "SCSceneBattle.h"
#include "Game/SCGameJoystick.h"

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
    return true;
}