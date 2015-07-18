/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIModuleFrames.cpp
 *  Desc:   ���ļ�����������������
 *  Author: Yish
 *  Date:   2015/7/18
 * ------------------------------------------------------------------------
 */

#include "SCUIModule.h"

typedef std::function<SCUIBase*(const std::string&)> UI_CREATE_FUNC;
static std::unordered_map<std::string, UI_CREATE_FUNC> l_UICreateFuncMap;

#define DECLARE_UI_CREATE_FUNC(name, filename, cls) l_UICreateFuncMap[name] = std::bind([&] { return new cls() })

///////////////////////////////////////////////////////////////////////////
// ���������������Ĵ�������

void SCUIModule::initUICreateFunc()
{
}