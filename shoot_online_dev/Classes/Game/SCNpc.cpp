#include "SCNpc.h"
#include "Components/SCComArmature.h"
#include "Components/SCComCollider.h"
#include "Components/SCComProperty.h"
#include "Data/SCDataModule.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;

SCNpc::SCNpc(GID gid, int tid) : SCObject(gid, tid), m_pEssence(NULL), m_iCurHP(0)
{
	_controller = new SCNpcController(this);
	_dispatcher = new SCNpcDispatcher(this);
}

SCNpc::~SCNpc()
{
	CC_SAFE_RELEASE(m_pEssence);

	CC_SAFE_DELETE(_controller);
	CC_SAFE_DELETE(_dispatcher);
}

bool SCNpc::init()
{
	if (!SCObject::init())
		return false;

	//获取npc的模板数据
	m_pEssence = (NPC_ESSENCE*)glb_getDataModule()->getTemplate(m_tid, DT_NPC_ESSENCE);
	if (m_pEssence)
		m_pEssence->retain();
	else
	{
		CCLOG("SCNpc::init, not found Essense! id : %d", m_tid);
		return false;
	}

	// 初始化组件
	addComponent(SC_COMPONENT_ARMATURE, (void*)m_pEssence->res_path.c_str());

	scComPropertyData data;
	data.atk_mode = m_pEssence->atk_mode;
	data.atk_interval = m_pEssence->atk_interval;
	data.bullet_id = m_pEssence->bullet_id;
	data.name = m_pEssence->name;
	data.max_hp = m_pEssence->max_hp;
	addComponent(SC_COMPONENT_PROPERTY, (void*)(&data));

	// 包围盒组件
	Rect rcBound(-32, 0, 64, 128);
	addComponent(SC_COMPONENT_COLLIDER, (void*)&rcBound);

	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getComponent(SC_COMPONENT_ARMATURE));
	pArmature->playAnimation("zhanli", true);
	pArmature->setScaleX(-1.0f);
    return true;
}

void SCNpc::update(float dt)
{
	SCObject::update(dt);


}

int SCNpc::DispatchMessage(const Message &msg)
{
    return _controller->MessageHandler(msg);
}