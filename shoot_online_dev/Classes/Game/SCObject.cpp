/*
 * ------------------------------------------------------------------------
 *  Name:   SCObject.cpp
 *  Desc:   游戏对象
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "cocos2d.h"
#include "SCObject.h"
#include "Utility/SCUtilityFunc.h"
#include "Components/SCComponentBase.h"
#include "Components/SCComArmature.h"
#include "Components/SCComCollider.h"
#include "Components/SCComPlayerMove.h"
#include "Components/SCComPlayerFSM.h"
#include "Components/SCComNPCProperty.h"
#include "Components/SCComSprite.h"
#include "Components/SCComBulletMove.h"
#include "Components/SCComBulletAtk.h"
#include "Components/SCComNPCMove.h"
#include "Components/SCComNPCFSM.h"
#include "Components/SCComNPCAI.h"
#include "Components/SCComPlayerProperty.h"

USING_NS_CC;

SCObject::SCObject(GID gid, int tid)
: m_id(gid), m_tid(tid), m_bActive(false), m_iFaceDirection(1)
{
	_world = glb_getWorld();
}

SCObject::~SCObject()
{
	ComponentList::iterator it = m_components.begin();
	while( it != m_components.end() )
	{
		delete (*it);
		++it;
	}
}

bool SCObject::init()
{
	if( !Node::init() )
		return false;

	return true;
}

void SCObject::update(float dt)
{
	// 更新组件
	for(ComponentList::iterator it=m_components.begin(); it!=m_components.end(); ++it)
	{
		(*it)->update(dt);
	}
}

void SCObject::addComponent(int comType, void* extraData)
{
	SCComponentBase* pComponent = NULL;

	switch(comType)
	{
	case SC_COMPONENT_ARMATURE:
		{
			const char* filename = (const char*)extraData;
			if( !filename )
				CCLOG("SCObject::addComponent , extraData for SCComArmature must not be null! comType: %d", comType);
			else
				pComponent = new SCComArmature(filename);
		}
		break;
	case SC_COMPONENT_COLLIDER:
		{
			Rect* pBound = (Rect*)extraData;
			if( !pBound )
				CCLOG("SCObject::addComponent, extraData for SCComCollider must not be null! comType: %d", comType);
			else
			{
				pComponent = new SCComCollider(*pBound);
			}
		}
		break;
	case SC_COMPONENT_PLAYERFSM:
		if( isHostPlayer() )
			pComponent = new SCComPlayerFSM();
		else
			CCLOG("SCObject::addComponent, This component(SC_COMPONENT_PLAYERFSM) can only be used by SCHostPlayer!");
		break;
	case SC_COMPONENT_PLAYERMOVE:
		if( isHostPlayer() )
			pComponent = new SCComPlayerMove();
		else
			CCLOG("SCObject::addComponent, This component(SC_COMPONENT_PLAYERMOVE) can only be used by SCHostPlayer!");
		break;
	case SC_COMPONENT_NPC_PROPERTY:
		{
			scComNPCPropertyData *propertyData = (scComNPCPropertyData *)extraData;
			pComponent = new SCComNPCProperty(*propertyData);
		}
		break;
	case SC_COMPONENT_SPRITE:
		{
			const char* filename = (const char*)extraData;
			if( !filename )
				CCLOG("SCObject::addComponent, extraData for SCComSprite must not be null! comType: %d", comType);
			else
				pComponent = new SCComSprite(filename);
		}
		break;
    case SC_COMPONENT_BULLET_ATK:
        {
            scComBulletAtkData *data = (scComBulletAtkData *)extraData;
            if (!data)
                CCLOG("SCObject::addComponent, extraData for SCComBulletAtk must not be null! comType: %d", comType);
            else
                pComponent = new SCComBulletAtk(*data);
        }
        break;
    case SC_COMPONENT_BULLET_MOVE:
        {
            scComBulletMoveData *data = (scComBulletMoveData *)extraData;
            if (!data)
                CCLOG("SCObject::addComponent, extraData for SCComBulletMove must not be null! comType: %d", comType);
            else
                pComponent = new SCComBulletMove(*data);
        }
		break;
	case SC_COMPONENT_NPCMOVE:
		if( isNPC() )
			pComponent = new SCComNPCMove();
		else
			CCLOG("SCObject::addComponent, This component(SC_COMPONENT_NPCMOVE) can only be used by SCNpc!");
		break;
	case SC_COMPONENT_NPCFSM:
		if( isNPC() )
			pComponent = new SCComNPCFSM();
		else
			CCLOG("SCObject::addComponent, This component(SC_COMPONENT_NPCFSM) can only be used by SCNpc!");
		break;
    case SC_COMPONENT_NPCAI:
        {
            const int* ai_tid = (const int*)extraData;
            if (!ai_tid)
                CCLOG("SCObject::addComponent , extraData for SCComArmature must not be null! comType: %d", comType);
            else
                pComponent = new SCComNPCAI(*ai_tid);
        }
        break;
    case SC_COMPONENT_PLAYER_PROPERTY:
        {
            scComPlayerPropertyData *data = (scComPlayerPropertyData*)extraData;
            if (!data)
                CCLOG("SCObject::addComponent, extraData for SCComPlayerProperty must not be null! comType: %d", comType);
            else
                pComponent = new SCComPlayerProperty(*data);
        }
        break;
	default:
		CCLOG("SCObject::addComponent, unknown component type!");
        break;
	}

	if( pComponent )
	{
		pComponent->setObject(this);
		if (pComponent->init())
			m_components.push_back(pComponent);
		else
			CCLOG("SCObject::addComponent, initialize the component (%d) failed!", comType);
	}
}

SCComponentBase* SCObject::getComponent(int comType)
{
	for(size_t i=0; i<m_components.size(); ++i)
	{
		if( m_components[i]->getType() == comType )
			return m_components[i];
	}

	return NULL;
}

void SCObject::setFaceDirection(int dir)
{
	m_iFaceDirection = dir;

	SCComArmature* pArmature = dynamic_cast<SCComArmature*>(getComponent(SC_COMPONENT_ARMATURE));
	if( pArmature )
		pArmature->refreshArmature();

	SCComSprite* pSprite = dynamic_cast<SCComSprite*>(getComponent(SC_COMPONENT_SPRITE));
	if( pSprite )
		pSprite->refreshSprite();

	SCComCollider* pCollider = dynamic_cast<SCComCollider*>(getComponent(SC_COMPONENT_COLLIDER));
	if( pCollider )
		pCollider->refreshBoundingBox();
}

void SCObject::sendMessage(const Message& msg)
{
	if (_world)
		_world->sendMessage(msg);
}