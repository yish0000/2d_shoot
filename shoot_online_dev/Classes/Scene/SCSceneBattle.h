//
//  SCSceneBattle.h
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#ifndef __ShootOnline__SCSceneBattle__
#define __ShootOnline__SCSceneBattle__

#include "SCSceneBase.h"
#include "Game/SCJoystick.h"

class SCSceneBattle : public SCSceneBase
{
public:
    SCSceneBattle();
    
    virtual bool init();
    
protected:
    SCJoystick* m_pJoystick;
};

#endif /* defined(__ShootOnline__SCSceneBattle__) */
