#include "SCComNPCAI.h"
#include "SCComNPCProperty.h"
#include "SCComArmature.h"
#include "Data/SCDataModule.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;

SCComNPCAI::SCComNPCAI(int ai_id)
: SCComponentBase(SC_COMPONENT_NPCAI), updateCount(0.f), inBattle(false)
{
    tid = ai_id;
}

bool SCComNPCAI::init()
{
    NPCAI_ESSENCE* m_pEssence = (NPCAI_ESSENCE*)glb_getDataModule()->getTemplate(tid, DT_NPCAI_ESSENCE);
    if (m_pEssence)
    {
        idle_mode = m_pEssence->idle_mode;
        switch (idle_mode)
        {
        case IDLE_AI_STAY:
            break;
        default:
            break;
        }
        atk_mode = m_pEssence->atk_mode;
        switch (atk_mode)
        {
        case ATK_AI_STAKE:
            break;
        case ATK_AI_TURRET:
            bullet_id = m_pEssence->bullet_id;
            atk_interval = m_pEssence->atk_interval;
            break;
        default:
            break;
        }

        //m_pGameObj->setFaceDirection(-1);
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

    if (inBattle)
    {
       
        switch (atk_mode)
        {
        case ATK_AI_STAKE:
            break;
        case ATK_AI_TURRET:
            updateCount += dt;
            DoTurretAttack();
            break;
        default:
            break;
        }
    }
    else
    {
        if (glb_getHostPlayer()->getPosition().getDistance(m_pGameObj->getPosition()) <= NPC_COMBAT_DISTANCE)
        {
            inBattle = true;
            return;
        }
        switch (idle_mode)
        {
        case ATK_AI_TURRET:
        default:
            break;
        }
    }
    return;
}

void SCComNPCAI::beAttack()
{
    return;
}

void SCComNPCAI::onDeath()
{

}

bool SCComNPCAI::IsZombie()
{
    SCComNPCProperty* pProperty = dynamic_cast<SCComNPCProperty*>(m_pGameObj->getComponent(SC_COMPONENT_NPC_PROPERTY));
    return pProperty->IsZombie();
}

void SCComNPCAI::DoTurretAttack()
{
    //ÅÐ¶ÏÍæ¼Ò·½Ïò
    if (glb_getHostPlayer()->getPosition().x - m_pGameObj->getPosition().x > 0)
    {
        m_pGameObj->setFaceDirection(1);
    }
    else
    {
        m_pGameObj->setFaceDirection(-1);
    }
    if (updateCount >= atk_interval)
    {
        SCComArmature* pArmature = dynamic_cast<SCComArmature*>(m_pGameObj->getComponent(SC_COMPONENT_ARMATURE));
        if (pArmature)
        {
//			pArmature->playAnimation("gongji", false, true, "zhanli");

            Point vBulletPos;
            if (pArmature->getBoneWorldPos("tou", vBulletPos))
            {
                m_pGameObj->getWorld()->GenerateBullet(bullet_id, vBulletPos, m_pGameObj);
                updateCount = 0;
            }
        }
    }
}