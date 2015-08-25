#include "SCBulletDispatcher.h"

void SCBulletDispatcher::SendAttackMessage(int64_t target, int atk_max, int atk_min)
{
	Message msg;
	attack_msg data;
	data.attacker = GID(0, 0);
	data.damage_high = atk_max;
	data.damage_low = atk_min;
	Message::BuildMessage(msg, MSG_ATTACK, GID(SC_OBJECT_NPC, target), getObject()->getGID(), getObject()->getPosition(), 0, 0,
		&data, sizeof(data));
	getObject()->sendMessage(msg);
}