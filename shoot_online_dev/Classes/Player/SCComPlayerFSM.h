/*
 * ------------------------------------------------------------------------
 *  Name:   SCComPlayerFSM.h
 *  Desc:   �����״̬��
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COMPLAYERFSM_H__
#define __SC_COMPLAYERFSM_H__

#include "SCComponentBase.h"

class SCComPlayerFSM : public SCComponentBase
{
public:
	SCComPlayerFSM();
	virtual ~SCComPlayerFSM();

	virtual bool init();
	virtual void update(float dt);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMPLAYERFSM_H__