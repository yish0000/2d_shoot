/*
 * ------------------------------------------------------------------------
 *  Name:   SCUtilityFunc.h
 *  Desc:   一些实用函数
 *  Author: Yish
 *  Date:   2015/5/22
 * ------------------------------------------------------------------------
 */

#ifndef __SC_UTILITYFUNC_H__
#define __SC_UTILITYFUNC_H__

#include <cocos2d.h>
#include "Module/SCModuleBase.h"

inline cocos2d::Scheduler* glb_getScheduler() { return cocos2d::Director::getInstance()->getScheduler(); }
inline cocos2d::Scene* glb_getCurScene() { return cocos2d::Director::getInstance()->getRunningScene(); }

SCModuleBase* glb_getModule(int moduleType);

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UTILITYFUNC_H__