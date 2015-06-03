//
//  SCSceneLogin.h
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#ifndef __ShootOnline__SCSceneLogin__
#define __ShootOnline__SCSceneLogin__

#include "SCSceneBase.h"

class SCSceneLogin : public SCSceneBase
{
public:
    SCSceneLogin();
    
    virtual bool init();
	CREATE_FUNC(SCSceneLogin);

    virtual void onEnter();
};

#endif /* defined(__ShootOnline__SCSceneLogin__) */
