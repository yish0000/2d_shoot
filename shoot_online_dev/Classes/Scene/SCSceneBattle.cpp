//
//  SCSceneBattle.cpp
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#include "SCSceneBattle.h"

static const char* JOYSTICK_BACK = "ui/joystick/back.png";
static const char* JOYSTICK_CENTER = "ui/joystick/center.png";

SCSceneBattle::SCSceneBattle()
    : SCSceneBase("Battle"), m_pJoystick(NULL)
{
}

bool SCSceneBattle::init()
{
    if( !SCSceneBase::init() )
        return false;
    
    m_pJoystick = SCJoystick::create(JOYSTICK_BACK, JOYSTICK_CENTER);
    addChild(m_pJoystick, 1000);
    return true;
}