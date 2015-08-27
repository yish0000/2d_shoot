#ifndef __SC_COMNPCAI_H__
#define __SC_COMNPCAI_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"
#include "../common/message.h"

enum 
{
    NPC_AI_INVALID  =   -1,
    NPC_AI_STAKE    =   0,
    NPC_AI_TURRET   =   1,
};

class SCComNPCAI : public SCComponentBase
{
public:
    SCComNPCAI() : SCComponentBase(SC_COMPONENT_NPCAI), mode(NPC_AI_INVALID), updateCount(0),inBattle(false) {}
    SCComNPCAI(int ai_id);
    virtual ~SCComNPCAI() {}

    bool IsZombie();

public:
    int tid;
    int mode;
    int bullet_id;
    int atk_interval;

    int updateCount;
    bool inBattle;
public:
    virtual bool init();
    virtual void update(float dt);
    void beAttack();
    void onDeath();
private:
    void DoTurretAttack();
};

#endif