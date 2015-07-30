/*
 * ------------------------------------------------------------------------
 *  Name:   SCObject.cpp
 *  Desc:   游戏对象
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCObject.h"
#include "cocos2d.h"
#include "Components/SCComponentBase.h"
#include "Components/SCComArmature.h"
#include "Components/SCComCollider.h"
#include "Components/SCComPlayerMove.h"
#include "Components/SCComPlayerFSM.h"
#include "Components/SCComProperty.h"
#include "Components/SCComSprite.h"
#include "Components/SCComBulletMove.h"
#include "Components/SCComBulletAtk.h"

USING_NS_CC;

SCObject::SCObject(GID gid, int tid)
	: m_id(gid), m_tid(tid), m_bActive(false)
{
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
		pComponent = new SCComPlayerFSM();
		break;
	case SC_COMPONENT_PLAYERMOVE:
		pComponent = new SCComPlayerMove();
		break;
	case SC_COMPONENT_PROPERTY:
		{
			scComPropertyData *propertyData = (scComPropertyData *)extraData;
			pComponent = new SCComProperty(*propertyData);
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
	default:
		CCLOG("SCObject::addComponent, unknown component type!");
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

	SCComCollider* pCollider = dynamic_cast<SCComCollider*>(getComponent(SC_COMPONENT_COLLIDER));
	if( pCollider )
		pCollider->refreshBoundingBox();
}