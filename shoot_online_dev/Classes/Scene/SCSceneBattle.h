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
#include "Game/SCGameJoystick.h"

class SCSceneBattle : public SCSceneBase
{
public:
    SCSceneBattle();
    
    virtual bool init();
	CREATE_FUNC(SCSceneBattle);

	void onBtnJump(cocos2d::Ref* pSender);
	void onBtnAttack(cocos2d::Ref* pSender);
    
protected:
    SCGameJoystick* m_pJoystick;
};

#endif /* defined(__ShootOnline__SCSceneBattle__) */
