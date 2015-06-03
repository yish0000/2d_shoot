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


enum
{
	SC_COMPONENT_UNKNOWN,

	SC_COMPONENT_ARMATURE,		// 骨骼动画
	SC_COMPONENT_PLAYERFSM,		// 主玩家状态机
};

class SCObject;

class SCComponentBase
{
public:
	SCComponentBase(SCObject* pObj) : m_pGameObj(pObj), m_iType(SC_COMPONENT_UNKNOWN), m_bActive(false) {}
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
};
///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMPONENTBASE_H__