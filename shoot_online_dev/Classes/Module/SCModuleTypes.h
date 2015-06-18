/*
 * ------------------------------------------------------------------------
 *  Name:   SCModuleTypes.h
 *  Desc:   模块类型
 *  Author: Yish
 *  Date:   2015/5/22
 * ------------------------------------------------------------------------
 */

#ifndef __SC_MODULETYPES_H__
#define __SC_MODULETYPES_H__

#include <string>

enum
{
	MODULE_TYPE_UNKNOWN,

	MODULE_TYPE_LOGIN,
	MODULE_TYPE_GAME,
	MODULE_TYPE_NETWORK,
	MODULE_TYPE_UI,
    MODULE_TYPE_PLAYER,     // 负责主玩家数据的管理
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_MODULETYPES_H__