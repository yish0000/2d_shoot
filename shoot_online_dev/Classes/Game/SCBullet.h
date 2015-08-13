#ifndef __SCBULLET_H__
#define __SCBULLET_H__

#include "SCObject.h"
#include <string>
#include "Data/SCDataTypes.h"
#include "SCBulletController.h"
#include "SCBulletDispatcher.h"

class SCBullet : public SCObject
{
private:
	BULLET_ESSENCE* m_pEssence;		// ×Óµ¯Ä£°å

public:
    SCBulletController* _controller;
    SCBulletDispatcher* _dispatcher;

public:
	SCBullet(GID gid, int tid);
    virtual ~SCBullet();

    virtual bool init();
	virtual void update(float dt);

	void setBirthPos(const cocos2d::Point& pos);

public:
    virtual int DispatchMessage(const Message& msg);
};


#endif //__SCBullet_H__