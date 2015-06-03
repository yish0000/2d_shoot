/*
 * ------------------------------------------------------------------------
 *  Name:   SCComCollider.h
 *  Desc:   Åö×²¼ì²â×é¼þ
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COMCOLLIDER_H__
#define __SC_COMCOLLIDER_H__

#include "SCComponentBase.h"

class SCComCollider : public SCComponentBase
{
public:
	SCComCollider();
	virtual ~SCComCollider();

	virtual bool init();
	virtual void update(float dt);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMCOLLIDER_H__