/*
 * ------------------------------------------------------------------------
 *  Name:   SCObject.cpp
 *  Desc:   游戏对象
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#include "SCObject.h"
#include "SCComponentBase.h"
#include "SCComArmature.h"
#include "SCComCollider.h"
#include "SCComPlayerMove.h"
#include "SCComPlayerFSM.h"
#include "cocos2d.h"

USING_NS_CC;

SCObject::SCObject(int64_t id, int tid)
	: m_id(id), m_tid(tid), m_bActive(false), m_iType(SC_OBJECT_UNKNOWN)
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

	// 初始化所有组件
	for(ComponentList::iterator it=m_components.begin(); it!=m_components.end(); ++it)
	{
		if( !(*it)->init() )
		{
			CCLOG("SCObject::init, initialize the component (%d) failed!", (*it)->getType());
			return false;
		}
	}

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
				CCLOG("SCObject::addComponent, extraData for SCComArmature must not be null!");
			else
				pComponent = new SCComArmature(filename);
		}
		break;
	case SC_COMPONENT_COLLIDER:
		{
			Rect* pBound = (Rect*)extraData;
			if( !pBound )
				CCLOG("SCObject::addComponent, extraData for SCComCollider must not be null!");
			else
				pComponent = new SCComCollider();
		}
		break;
	case SC_COMPONENT_PLAYERFSM:
		pComponent = new SCComPlayerFSM();
		break;
	case SC_COMPONENT_PLAYERMOVE:
		pComponent = new SCComPlayerMove();
		break;
	default:
		CCLOG("SCObject::addComponent, unknown component type!");
	}

	if( pComponent )
	{
		pComponent->setObject(this);
		m_components.push_back(pComponent);
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