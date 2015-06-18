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

class SCPlayerModule;
class SCNetworkModule;
class UIModule;
class SCHostPlayer;
class SCTiledMap;
class SCStage;

inline cocos2d::Scheduler* glb_getScheduler() { return cocos2d::Director::getInstance()->getScheduler(); }
inline cocos2d::Scene* glb_getCurScene() { return cocos2d::Director::getInstance()->getRunningScene(); }

int glb_getGameState();
SCHostPlayer* glb_getHostPlayer();
SCStage* glb_getWorld();
SCTiledMap* glb_getTiledMap();

SCModuleBase* glb_getModule(int moduleType);
inline SCPlayerModule* glb_getPlayerModule() { return (SCPlayerModule*)glb_getModule(MODULE_TYPE_PLAYER); }
inline UIModule* glb_getUIModule() { return (UIModule*)glb_getModule(MODULE_TYPE_UI); }
inline SCNetworkModule* glb_getNetworkModule() { return (SCNetworkModule*)glb_getModule(MODULE_TYPE_NETWORK); }

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UTILITYFUNC_H__