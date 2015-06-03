/*
 * ------------------------------------------------------------------------
 *  Name:   SCObject.h
 *  Desc:   ��Ϸ����
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_OBJECT_H__
#define __SC_OBJECT_H__

#include "2d/CCNode.h"
#include "SCComponentBase.h"

enum
{
	SC_OBJECT_UNKNOWN,

	SC_OBJECT_HOSTPLAYER,
	SC_OBJECT_NPC,
};

/** ��Ϸ�ڵĶ���
*/
class SCObject : public cocos2d::Node
{
	typedef std::vector<SCComponentBase*> ComponentList;

public:
	SCObject(int64_t id, int tid);
	virtual ~SCObject();

	virtual bool init();
	virtual void update(float dt);

	void addComponent(int comType, void* extraData);
	SCComponentBase* getComponent(int comType);

	int getType() const { return m_iType; }
	bool isHostPlayer() const { return m_iType == SC_OBJECT_HOSTPLAYER; }
	bool isNPC() const { return m_iType == SC_OBJECT_NPC; }
	
	int getFaceDirection() const { return m_iFaceDirection; }
	void setFaceDirection(int dir);

	void setActive(bool bActive) { m_bActive = bActive; }
	bool isActive() const { return m_bActive; }

	int getTID() const { return m_tid; }
	int64_t getID() const { return m_id; }

protected:
	int64_t m_id;				// ����ID
	int m_tid;					// ģ��ID
	int m_iType;				// ��������
	bool m_bActive;				// �ö����Ƿ񼤻�
	int m_iFaceDirection;		// ����

	ComponentList m_components;	// ����б�
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_OBJECT_H__