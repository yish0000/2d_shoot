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

	int m_iCurHP;				// 当前血量

public:
    SCNpcController* _controller;
    SCNpcDispatcher* _dispatcher;

public:
	SCNpc(GID gid, int tid);
    virtual ~SCNpc();

    virtual bool init();
	virtual void update(float dt);

	int getCurHP() const { return m_iCurHP; }

public:
    virtual int DispatchMessage(const Message& msg);
};


#endif //__SCNPC_H__