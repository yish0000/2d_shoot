#ifndef __SC_COMNPCAI_H__
#define __SC_COMNPCAI_H__

#include "../SCComponentBase.h"
#include "../../SCWorld.h"
#include "../../common/message.h"

enum 
{
    NPC_AI_INVALID  =   -1,
    NPC_AI_STAKE    =   0,
    NPC_AI_TURRET   =   1,
};

class SCComNPCAI : public SCComponentBase
{
public:
    SCComNPCAI() : SCComponentBase(SC_COMPONENT_PROPERTY), aiMode(NPC_AI_INVALID) {}
    virtual ~SCComNPCAI() {}

    bool IsZombie();

public:
    int aiMode;
    virtual bool init() = 0;
    virtual void update(float dt) = 0;
    virtual void beAttack() = 0;
    virtual void onDeath() = 0;
};

#endif