/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIModuleFrames.cpp
 *  Desc:   本文件用来创建各个界面
 *  Author: Yish
 *  Date:   2015/7/18
 * ------------------------------------------------------------------------
 */

#include "SCUIModule.h"

// 这里包含界面的头文件
#include "SCUISkill.h"

typedef std::function<SCUIBase*()> UI_CREATE_FUNC;
static std::unordered_map<std::string, UI_CREATE_FUNC> l_UICreateFuncMap;

#define DECLARE_UI_CREATE_FUNC(name, cls) { \
	auto funcPtr = [&]() -> SCUIBase* { return new cls(name, m_UIMetas[name].filename); }; \
	l_UICreateFuncMap[name] = funcPtr; \
}

///////////////////////////////////////////////////////////////////////////
// 这里关联各个界面的创建函数

void SCUIModule::initUICreateFunc()
{
	if( l_UICreateFuncMap.size() )
		return;

	DECLARE_UI_CREATE_FUNC("Skill", SCUISkill);
}

// 创建指定的界面
SCUIBase* SCUIModule::createUIFrame(const std::string& name)
{
	std::unordered_map<std::string, UI_CREATE_FUNC>::iterator it = l_UICreateFuncMap.find(name);
	if( it == l_UICreateFuncMap.end() )
		return NULL;
	return it->second();
}