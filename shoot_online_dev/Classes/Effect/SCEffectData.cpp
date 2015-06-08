/*
 * ------------------------------------------------------------------------
 *  Name:   SCEffectData.cpp
 *  Desc:   特效数据
 *  Author: Yish
 *  Date:   2015/6/9
 * ------------------------------------------------------------------------
 */

#include "SCEffectData.h"
#include "SCEffectElement.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;

SCEffectData::SCEffectData()
	: m_iFrameCount(0), m_iFrontBackDivide(0), m_iLoopCount(1)
	, m_iShakeEventFrame(-1), m_iShakeEventData(0)
{
}

SCEffectData::~SCEffectData()
{
}

