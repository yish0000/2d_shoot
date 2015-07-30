#include "SCBullet.h"
#include "Data/SCDataModule.h"
#include "Utility/SCUtilityFunc.h"
#include "Components/SCComSprite.h"
#include "Components/SCComBulletMove.h"
#include "Components/SCComBulletAtk.h"

USING_NS_CC;

SCBullet::SCBullet(GID gid, int tid) : SCObject(gid, tid), m_pEssence(NULL)
{
	_controller = new SCBulletController(this);
	_dispatcher = new SCBulletDispatcher(this);
}

SCBullet::~SCBullet()
{
	CC_SAFE_RELEASE(m_pEssence);

	CC_SAFE_DELETE(_controller);
	CC_SAFE_DELETE(_dispatcher);
}

bool SCBullet::init()
{
	//获取子弹的模板数据
	m_pEssence = (BULLET_ESSENCE*)glb_getDataModule()->getTemplate(m_tid, DT_BULLET_ESSENCE);
	if (m_pEssence)
		m_pEssence->retain();
	else
	{
		CCLOG("SCBullet::init, not found Essense! id : %d", m_tid);
		return false;
	}

	//攻击属性
	scComBulletAtkData atkData;
	atkData.atk_max = m_pEssence->atk_max;
	atkData.atk_min = m_pEssence->atk_min;
	addComponent(SC_COMPONENT_BULLET_ATK, (void *)(&atkData));

    scComBulletMoveData moveData;
    moveData.speed = m_pEssence->move_speed;
    addComponent(SC_COMPONENT_BULLET_MOVE, (void *)(&moveData));
	// 图片组件
	addComponent(SC_COMPONENT_SPRITE, (void*)m_pEssence->res_path.c_str());

	// 碰撞组件
	Rect rcBound(-5, -5, 10, 10);
	addComponent(SC_COMPONENT_COLLIDER, (void*)&rcBound);

    return true;
}

void SCBullet::update(float dt)
{
	SCObject::update(dt);

}

int SCBullet::DispatchMessage(const Message &msg)
{
    return _controller->MessageHandler(msg);
}