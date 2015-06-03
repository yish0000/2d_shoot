//
//  SCSceneMain.cpp
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#include "SCSceneMain.h"

SCSceneMain::SCSceneMain()
    : SCSceneBase("Main")
{
}

bool SCSceneMain::init()
{
	if( !SCSceneBase::init() )
		return false;

	return true;
}