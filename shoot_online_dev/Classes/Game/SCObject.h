/*
 * ------------------------------------------------------------------------
 *  Name:   SCObject.h
 *  Desc:   游戏对象
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_OBJECT_H__
#define __SC_OBJECT_H__

#include "2d/CCNode.h"
#include "Game/common/type.h"
#include "Game/common/message.h"
#include "Components/SCComponentBase.h"


class SCWorld;

/** 游戏内的对象
*/
class SCObject : public cocos2d::Node
{
	typedef std::vector<SCComponentBase*> ComponentList;

public:
    SCObject() : m_tid(0), m_bActive(false) {}
	SCObject(GID gid, int tid);
	virtual ~SCObject();

	virtual bool init();
	virtual void update(float dt);

	void addComponent(SCComponentBase* pCom);
	void addComponent(int comType, void* extraData);
	SCComponentBase* getComponent(int comType);

	int getType() const { return m_id.type; }
	bool isHostPlayer() const { return m_id.type == SC_OBJECT_HOSTPLAYER; }
	bool isNPC() const { return m_id.type == SC_OBJECT_NPC; }
	
    bool isActive() const { return m_bActive; }
    void setActive(bool bActive) { m_bActive = bActive; }
    
	int getFaceDirection() const { return m_iFaceDirection; }
	void setFaceDirection(int dir);

	int getTID() const { return m_tid; }
	int64_t getID() const { return m_id.id; }
    GID getGID() const { return m_id; }

    SCWorld* getWorld() const { return _world; }
	void setWorld(SCWorld* pWorld) { _world = pWorld; }
	// 发送消息
	virtual void sendMessage(const Message& msg);
    
    virtual int DispatchMessage(const Message& msg) = 0; 
    
protected:
    GID m_id;                   // 对象ID, 游戏内id＋类型
	int m_tid;					// 模板ID, 玩家此项为-1
	bool m_bActive;				// 该对象是否激活
	int m_iFaceDirection;		// 朝向
    SCWorld* _world;            // 世界指针
    
	ComponentList m_components;	// 组件列表
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_OBJECT_H__