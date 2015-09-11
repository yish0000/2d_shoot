#ifndef __SCNPC_H__
#define __SCNPC_H__

#include "SCObject.h"
#include <string>
#include "SCNpcController.h"
#include "SCNpcDispatcher.h"
#include "Data/SCDataTypes.h"

class SCNpc : public SCObject
{
private:
	NPC_ESSENCE* m_pEssence;	// NPC模板

public:
    SCNpcController* _controller;
    SCNpcDispatcher* _dispatcher;

public:
	SCNpc(GID gid, int tid);
    virtual ~SCNpc();

    virtual bool init();
	virtual void update(float dt);

	// 销毁尸体
	void doDispear(float fDelay = 1.0f);

	// 是否已经死亡
	bool isZombied();

	// 获取NPC的包围盒
	cocos2d::Rect getBoundingBox();
	// 获取NPC的模板数据
	const NPC_ESSENCE* getEssence() const { return m_pEssence; }

public:
    virtual int DispatchMessage(const Message& msg);

protected:
	void onDispearing(float dt);
};


#endif //__SCNPC_H__