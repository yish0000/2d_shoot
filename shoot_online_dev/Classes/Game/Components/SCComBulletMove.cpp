#include "SCComBulletMove.h"

SCComBulletMove::SCComBulletMove(scComBulletAtkMoveData& data)
    :SCComponentBase(SC_COMPONENT_BULLET_MOVE)
{
    speed = data.speed;
    birth_pos = data.birthPos; 
}

bool SCComBulletMove::init()
{
    return true;
}

void SCComBulletMove::update(float dt)
{
    //ÒÆ¶¯
}