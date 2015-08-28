#include "SCComBulletAtk.h"

SCComBulletAtk::SCComBulletAtk(scComBulletAtkData &data)
    :SCComponentBase(SC_COMPONENT_BULLET_ATK)
{
    m_atk_max = data.atk_max;
    m_atk_min = data.atk_min;
}



bool SCComBulletAtk::init()
{
    return true;
}

void SCComBulletAtk::update(float dt)
{
}

void SCComBulletAtk::DoAttack(GID target)
{
    SCBullet *object = dynamic_cast<SCBullet*>(m_pGameObj);
    object->_dispatcher->SendAttackMessage(target, m_atk_max, m_atk_min);
}

