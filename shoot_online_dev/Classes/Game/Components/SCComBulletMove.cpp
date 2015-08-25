#include "SCComBulletMove.h"
#include "SCComCollider.h"
#include "../SCWorld.h"
#include "Utility/SCUtilityFunc.h"

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
	//移动
	Point oldPos = m_pGameObj->getPosition();
	Point newPos = oldPos;
	if (getObject()->getFaceDirection() > 0)
		newPos.x += m_speed * dt;
	else
		newPos.x -= m_speed * dt;

	m_pGameObj->setPosition(newPos);

	if (newPos.getDistance(m_birth_pos) > 1000)
	{
		m_pGameObj->removeFromParent();
	}

	// 碰撞检测
	SCComCollider* pCollider = dynamic_cast<SCComCollider*>(m_pGameObj->getComponent(SC_COMPONENT_COLLIDER));
	SCWorld* pWorld = glb_getWorld();
	std::vector<int64_t> npcList;
	pWorld->checkNPCCollision(pCollider->getBoundingBox(), oldPos, newPos, npcList);
	if (npcList.size() > 0)
	{
		m_pGameObj->removeFromParent();

		// 目标受伤
		for (size_t i = 0; i < npcList.size(); ++i)
		{
			attack_msg data;
			data.attacker = glb_getHostPlayer()->getGID();
			data.damage_high = 5;
			data.damage_low = 3;
			Message msg;
			Message::BuildMessage(msg, MSG_ATTACK, GID(SC_OBJECT_NPC, npcList[i]), m_pGameObj->getGID(), m_pGameObj->getPosition(), 0, 0,
				&data, sizeof(data));
			m_pGameObj->sendMessage(msg);
		}
	}
}