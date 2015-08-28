#ifndef __SC_COMNPCAI_H__
#define __SC_COMNPCAI_H__

#include "SCComponentBase.h"
#include "../SCWorld.h"
#include "../common/message.h"

enum IDLE_MODE
{
    IDLE_AI_INVALID =   0,
    IDLE_AI_STAY    =   1,
    //TODO IDLE_AI_WANDER  =   1,
};
enum ATK_MODE
{
    ATK_AI_INVALID  =   0,
    ATK_AI_STAKE    =   1,
    ATK_AI_TURRET   =   2,
};

class SCComNPCAI : public SCComponentBase
{
public:
    SCComNPCAI() : SCComponentBase(SC_COMPONENT_NPCAI), idle_mode(IDLE_AI_INVALID), atk_mode(ATK_AI_STAKE),updateCount(0.f),inBattle(false) {}
    SCComNPCAI(int ai_id);
    virtual ~SCComNPCAI() {}

    bool IsZombie();

public:
    int tid;
    int idle_mode;
    int atk_mode;
    int bullet_id;
    int atk_interval;

    float updateCount;
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