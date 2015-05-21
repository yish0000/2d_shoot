/*
 * ------------------------------------------------------------------------
 *  Name:   SCModuleBase.h
 *  Desc:   Ä£¿é»ùÀà
 *  Author: Yish
 *  Date:   2015/5/20
 * ------------------------------------------------------------------------
 */

#ifndef __SC_MODULEBASE_H__
#define __SC_MODULEBASE_H__

#include "Common/SCEvent.h"

class SCModuleBase : public SCEventListener, public SCEventDispatcher
{
public:
	SCModuleBase();
	virtual ~SCModuleBase();
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_MODULEBASE_H__