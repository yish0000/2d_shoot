/*
 * ------------------------------------------------------------------------
 *  Name:   SCComponentBase.h
 *  Desc:   组件基类
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COMPONENTBASE_H__
#define __SC_COMPONENTBASE_H__

#include <string>

enum
{
    SC_COMPONENT_UNKNOWN,

    SC_COMPONENT_ARMATURE,		// 骨骼动画
    SC_COMPONENT_PLAYERFSM,		// 玩家状态机
    SC_COMPONENT_PLAYERMOVE,	// 玩家移动控制
    SC_COMPONENT_COLLIDER,		// 碰撞检测
    SC_COMPONENT_PROPERTY,      //  属性 
    SC_COMPONENT_WEAPON,        //  武器
    SC_COMPONENT_BULLET_ATK,    // 子弹伤害
    SC_COMPONENT_BULLET_MOVE,   // 子弹移动
	SC_COMPONENT_SPRITE,		// 2D精灵
};

class SCObject;

class SCComponentBase
{
	friend class SCObject;

public:
	SCComponentBase(int type) : m_pGameObj(NULL), m_iType(type), m_bActive(false) {}
	virtual ~SCComponentBase() {}

	virtual bool init() = 0;
	virtual void update(float dt) = 0;

	int getType() const { return m_iType; }

    bool isActive() const { return m_bActive; }
    void setActive(bool bActive) { m_bActive = bActive; }

	SCObject* getObject() { return m_pGameObj; }

protected:
	int m_iType;
	SCObject* m_pGameObj;
	bool m_bActive;

	void setObject(SCObject* pObj) { m_pGameObj = pObj; }
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMPONENTBASE_H__