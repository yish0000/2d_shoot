//
//  SCNpcController.h
//  ShootOnline
//
//  Created by 琰 陈 on 15/6/18.
//
//

#ifndef __ShootOnline__SCNpcController__
#define __ShootOnline__SCNpcController__

#include <stdio.h>
#include "Game/common/mvc.h"

class SCNpc;
class SCNpcController : public Controller
{
private:
    SCNpc *gameObject;
public:
    SCNpcController() {}
    virtual ~SCNpcController() {}
    virtual int MessageHandler(const Message& msg);
};
#endif /* defined(__ShootOnline__SCNpcController__) */
