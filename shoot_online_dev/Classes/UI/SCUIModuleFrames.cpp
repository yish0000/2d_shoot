/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIModuleFrames.cpp
 *  Desc:   本文件用来创建各个界面
 *  Author: Yish
 *  Date:   2015/7/18
 * ------------------------------------------------------------------------
 */

#include "SCUIModule.h"

typedef std::function<SCUIBase*(const std::string&)> UI_CREATE_FUNC;
static std::unordered_map<std::string, UI_CREATE_FUNC> l_UICreateFuncMap;

#define DECLARE_UI_CREATE_FUNC(name, filename, cls) l_UICreateFuncMap[name] = std::bind([&] { return new cls() })

///////////////////////////////////////////////////////////////////////////
// 这里关联各个界面的创建函数

void SCUIModule::initUICreateFunc()
{
}