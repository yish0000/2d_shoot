//
//  SCSceneMain.h
//  ShootOnline
//
//  Created by Yish on 15/6/3.
//
//

#ifndef __ShootOnline__SCSceneMain__
#define __ShootOnline__SCSceneMain__

#include "SCSceneBase.h"

class SCSceneMain : public SCSceneBase
{
public:
    SCSceneMain();

	virtual bool init();
	CREATE_FUNC(SCSceneMain);

};

#endif /* defined(__ShootOnline__SCSceneMain__) */
