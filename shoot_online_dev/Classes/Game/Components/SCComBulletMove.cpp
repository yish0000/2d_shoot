#include "SCComBulletMove.h"

USING_NS_CC;

SCComBulletMove::SCComBulletMove(scComBulletMoveData& data)
    :SCComponentBase(SC_COMPONENT_BULLET_MOVE)
{
    m_speed = data.speed;
    m_birth_pos = data.birthPos; 
}

bool SCComBulletMove::init()
{
	m_pGameObj->setPosition(m_birth_pos);
    return true;
}

void SCComBulletMove::update(float dt)
{
	//ÒÆ¶¯
	Point newPos = m_pGameObj->getPosition();
	if (getObject()->getFaceDirection() > 0)
		newPos.x += m_speed * dt;
	else
		newPos.x -= m_speed * dt;

	m_pGameObj->setPosition(newPos);

	if (newPos.getDistance(m_birth_pos) > 1000)
	{
		m_pGameObj->removeFromParent();
	}
}