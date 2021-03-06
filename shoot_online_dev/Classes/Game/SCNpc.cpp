#include "SCNpc.h"
#include "Components/SCComArmature.h"
#include "Components/SCComCollider.h"
#include "Components/SCComNPCProperty.h"
#include "Data/SCDataModule.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;

SCNpc::SCNpc(GID gid, int tid) : SCObject(gid, tid), m_pEssence(NULL)
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

	scComNPCPropertyData data;
//	data.name = m_pEssence->name;
	data.max_hp = m_pEssence->max_hp;
	addComponent(SC_COMPONENT_NPC_PROPERTY, (void*)(&data));

	// 包围盒组件
	Rect rcBound(-32, 0, 64, 128);
	if (m_tid == 726)
		rcBound.setRect(-256, 0, 512, 512);
	addComponent(SC_COMPONENT_COLLIDER, (void*)&rcBound);

	// 状态机组件
	addComponent(SC_COMPONENT_NPCFSM, NULL);
	// 移动组件
	addComponent(SC_COMPONENT_NPCMOVE, NULL);

    //AI 组件
    addComponent(SC_COMPONENT_NPCAI, (void*)&(m_pEssence->ai_mode));

	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getComponent(SC_COMPONENT_ARMATURE));
	pArmature->playAnimation("zhanli", true);
	pArmature->setInitFaceDir(-1);

    setActive(true);
	setScale(m_pEssence->scale);
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

cocos2d::Rect SCNpc::getBoundingBox()
{
	SCComCollider* pCollider = dynamic_cast<SCComCollider*>(getComponent(SC_COMPONENT_COLLIDER));
	if (pCollider)
		return pCollider->getBoundingBox();
	else
	{
		CCASSERT(0, "Cannot find the collider component!");
		return Rect(0, 0, 0, 0);
	}
}

bool SCNpc::isZombied()
{
	SCComNPCProperty* pProp = dynamic_cast<SCComNPCProperty*>(getComponent(SC_COMPONENT_NPC_PROPERTY));
	return pProp ? pProp->IsZombie() : true;
}

void SCNpc::doDispear(float fDelay)
{
	if (isZombied())
	{
		scheduleOnce(schedule_selector(SCNpc::onDispearing), fDelay);
	}
}

void SCNpc::onDispearing(float dt)
{
	Sequence* pAction = Sequence::create(
		FadeOut::create(0.6f), RemoveSelf::create(), nullptr);
	setCascadeOpacityEnabled(true);
	runAction(pAction);
}