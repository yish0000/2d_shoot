/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIModuleFrames.cpp
 *  Desc:   ���ļ�����������������
 *  Author: Yish
 *  Date:   2015/7/18
 * ------------------------------------------------------------------------
 */

#include "SCUIModule.h"

// ������������ͷ�ļ�
#include "SCUISkill.h"

typedef std::function<SCUIBase*()> UI_CREATE_FUNC;
static std::unordered_map<std::string, UI_CREATE_FUNC> l_UICreateFuncMap;

#define DECLARE_UI_CREATE_FUNC(name, cls) { \
	auto funcPtr = [&]() -> SCUIBase* { return new cls(name, m_UIMetas[name].filename); }; \
	l_UICreateFuncMap[name] = funcPtr; \
}

///////////////////////////////////////////////////////////////////////////
// ���������������Ĵ�������

void SCUIModule::initUICreateFunc()
{
	if( l_UICreateFuncMap.size() )
		return;

	DECLARE_UI_CREATE_FUNC("Skill", SCUISkill);
}

// ����ָ���Ľ���
SCUIBase* SCUIModule::createUIFrame(const std::string& name)
{
	std::unordered_map<std::string, UI_CREATE_FUNC>::iterator it = l_UICreateFuncMap.find(name);
	if( it == l_UICreateFuncMap.end() )
		return NULL;
	return it->second();
}