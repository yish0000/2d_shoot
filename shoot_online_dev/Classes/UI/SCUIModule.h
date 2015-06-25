/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIModule.h
 *  Desc:   UI模块
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#ifndef __SC_UIMODULE_H__
#define __SC_UIMODULE_H__

#include <unordered_map>
#include "Module/SCModuleBase.h"

class SCUIBase;

class SCUIModule : public SCModuleBase
{
public:

	typedef std::unordered_map<std::string, SCUIBase*> UITable;

public:
	SCUIModule();
	virtual ~SCUIModule();
    
    virtual bool init();
    virtual void update(float dt);
    
    virtual void clearResources();

	// 获取指定的界面
	SCUIBase* getUIFrame(const std::string& name);

	float getUIScale() const { return m_fUIScale; }
	
protected:
	UITable m_UITable;
	float m_fUIScale;

protected:
	// Event handlers.
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UIMODULE_H__