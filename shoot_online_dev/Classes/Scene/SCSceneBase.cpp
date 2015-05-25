/*
 * ------------------------------------------------------------------------
 *  Name:   SCSceneBase.cpp
 *  Desc:   场景对象基类
 *  Author: Yish
 *  Date:   2015/5/24
 *  ----------------------------------------------------------------------
 *  CopyRight (C) YishPear Studio. All right observed.
 * ------------------------------------------------------------------------
 */

#include "SCSceneBase.h"
#include "2d/CCLayer.h"

USING_NS_CC;

SCSceneBase::SCSceneBase(const std::string& name)
	: m_sName(name), m_pUILayer(NULL)
{
}

SCSceneBase::~SCSceneBase()
{
}

bool SCSceneBase::init()
{
	if( !Scene::init() )
		return false;

	m_pUILayer = Layer::create();
	addChild(m_pUILayer, SCENELAYER_ZORDER_UI);
	return true;
}