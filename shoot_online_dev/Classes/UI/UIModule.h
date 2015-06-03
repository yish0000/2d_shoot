/*
 * ------------------------------------------------------------------------
 *  Name:   UIModule.h
 *  Desc:   UI模块
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#ifndef __SC_UIMODULE_H__
#define __SC_UIMODULE_H__

#include "Module/SCModuleBase.h"

class UIModule : public SCModuleBase
{
public:
	UIModule();
	virtual ~UIModule();
    
    virtual bool init();
    virtual void update(float dt);
    
    virtual void clearResources();

	float getUIScale() const { return m_fUIScale; }

protected:
	float m_fUIScale;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UIMODULE_H__