/*
 * ------------------------------------------------------------------------
 *  Name:   SCSceneBase.h
 *  Desc:   场景基类
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#ifndef __SC_SCENEBASE_H__
#define __SC_SCENEBASE_H__

#include "2d/CCScene.h"

/** 场景各个层的Z值
*/
enum
{
	SCENELAYER_ZORDER_NPC = 1,
	SCENELAYER_ZORDER_BOTPLAYER = 2,
	SCENELAYER_ZORDER_ELSEPLAYER = 3,
	SCENELAYER_ZORDER_HOSTPLAYER = 4,
	SCENELAYER_ZORDER_SUBOBJECT = 6,
	SCENELAYER_ZORDER_EFFECT = 100,
	SCENELAYER_ZORDER_INPUT = 1000,
	SCENELAYER_ZORDER_UI = 10000,
};

class SCSceneBase : public cocos2d::Scene
{
public:
	SCSceneBase(const std::string& name);
	virtual ~SCSceneBase();

	virtual bool init();

	const std::string& getSceneName() const { return m_sName; }
	cocos2d::Layer* getUILayer() const { return m_pUILayer; }

protected:
	std::string m_sName;
	cocos2d::Layer* m_pUILayer;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_SCENEBASE_H__