/*
 * ------------------------------------------------------------------------
 *  Name:   SCComponentBase.h
 *  Desc:   �������
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

	SC_COMPONENT_ARMATURE,		// ��������
	SC_COMPONENT_PLAYERFSM,		// ���״̬��
	SC_COMPONENT_PLAYERMOVE,	// ����ƶ�����
	SC_COMPONENT_COLLIDER,		// ��ײ���
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