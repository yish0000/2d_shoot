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
#include "SCUITypes.h"

class SCUIBase;

/** UI模块
*/
class SCUIModule : public SCModuleBase
{
public:

	struct UIMetaInfo
	{
		std::string name;
		std::string filename;
		UIFrameType type;
		bool visible;				// 初始时是否显示
		std::string parent_name;	// 父界面
		int zOrder;					// z值
	};

	typedef std::unordered_map<std::string, UIMetaInfo> UIMetaInfoTable;
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