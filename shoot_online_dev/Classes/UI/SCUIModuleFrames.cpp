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
#include "SCUIOption.h"
#include "SCUIStart.h"
#include "SCUICustom.h"
#include "SCUIStage.h"
#include "SCUIChapter.h"

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

	DECLARE_UI_CREATE_FUNC("Battlemain", SCUISkill);
	DECLARE_UI_CREATE_FUNC("Option", SCUIOption);
	DECLARE_UI_CREATE_FUNC("Start", SCUIStart);
	DECLARE_UI_CREATE_FUNC("Custom", SCUICustom);
	DECLARE_UI_CREATE_FUNC("Stage", SCUIStage);
	DECLARE_UI_CREATE_FUNC("Chapter", SCUIChapter);
}

// ����ָ���Ľ���
SCUIBase* SCUIModule::createUIFrame(const std::string& name)
{
	std::unordered_map<std::string, UI_CREATE_FUNC>::iterator it = l_UICreateFuncMap.find(name);
	if( it == l_UICreateFuncMap.end() )
		return NULL;
	return it->second();
}