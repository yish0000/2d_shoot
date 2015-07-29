#include "SCComBulletAtk.h"

SCComBulletAtk::SCComBulletAtk(scComBulletAtkData &data)
    :SCComponentBase(SC_COMPONENT_BULLET_ATK)
{
    atk_max = data.atk_max;
    atk_min = data.atk_min;
}



bool SCComBulletAtk::init()
{
    return true;
}

void SCComBulletAtk::update(float dt)
{
}

void SCComBulletAtk::DoAttack(int64_t target)
{
    SCBullet *object = dynamic_cast<SCBullet *>(m_pGameObj);
    object->_dispatcher->SendAttackMessage(target, atk_max, atk_min);
}

