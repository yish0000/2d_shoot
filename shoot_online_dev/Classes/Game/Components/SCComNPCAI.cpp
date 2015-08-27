#include "SCComNPCAI.h"
#include "SCComProperty.h"
#include "SCComArmature.h"
#include "Data/SCDataModule.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;

SCComNPCAI::SCComNPCAI(int ai_id)
: SCComponentBase(SC_COMPONENT_NPCAI), updateCount(0), inBattle(false)
{
    tid = ai_id;
}

bool SCComNPCAI::init()
{
    NPCAI_ESSENCE* m_pEssence = (NPCAI_ESSENCE*)glb_getDataModule()->getTemplate(tid, DT_NPC_ESSENCE);
    if (m_pEssence)
    {
        mode = m_pEssence->mode;
        switch (mode)
        {
        case NPC_AI_STAKE:
            break;
        case NPC_AI_TURRET:
            bullet_id = m_pEssence->bullet_id;
            atk_interval = m_pEssence->atk_interval;
            break;
        default:
            break;
        }
    }
    else
    {
        CCLOG("SCNPCAI::init, not found Essense! id : %d", tid);
        return false;
    }
    return true;
}


void SCComNPCAI::update(float dt)
{
    //³¬³ö¾àÀëÔòÐÝÃß
    if (glb_getHostPlayer()->getPosition().getDistance(m_pGameObj->getPosition()) > NPC_TRIGGER_DISTANCE)
        return;
    if (IsZombie())
        return;

    updateCount += dt;
    switch (mode)
    {
    case NPC_AI_STAKE:
        break;
    case NPC_AI_TURRET:
        DoTurretAttack();
        break;
    default:
        break;
    }
}

void SCComNPCAI::beAttack()
{
    return;
}

void SCComNPCAI::onDeath()
{
    switch (mode)
    {
    case NPC_AI_STAKE:
        break;
    case NPC_AI_TURRET:
        DoTurretAttack();
        break;
    default:
        break;
    }
}

bool SCComNPCAI::IsZombie()
{
    SCComProperty* pProperty = dynamic_cast<SCComProperty*>(m_pGameObj->getComponent(SC_COMPONENT_PROPERTY));
    return pProperty->IsZombie();
}

void SCComNPCAI::DoTurretAttack()
{
    if (updateCount >= atk_interval)
    {
        SCComArmature* pArmature = dynamic_cast<SCComArmature*>(m_pGameObj->getComponent(SC_COMPONENT_ARMATURE));
        if (pArmature)
        {
            Point vBulletPos;
            if (!pArmature->getBoneWorldPos("tou", vBulletPos))
            {
                m_pGameObj->getWorld()->GenerateBullet(bullet_id, vBulletPos);
                updateCount = 0;
            }
        }
    }
}