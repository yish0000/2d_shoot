//
//  SCSceneLogin.cpp
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#include "SCSceneLogin.h"

SCSceneLogin::SCSceneLogin()
    : SCSceneBase("Login")
{
}

bool SCSceneLogin::init()
{
    if( !SCSceneBase::init() )
        return false;
    
    return true;
}

void SCSceneLogin::onEnter()
{
    SCSceneBase::onEnter();
    
}