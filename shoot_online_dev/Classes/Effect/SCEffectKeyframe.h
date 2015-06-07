/*
 * ------------------------------------------------------------------------
 *  Name:   SCEffectKeyframe.h
 *  Desc:   特效关键帧数据
 *  Author: Yish
 *  Date:   2015/6/7
 * ------------------------------------------------------------------------
 */

#ifndef __SC_EFFECTKEYFRAME_H__
#define __SC_EFFECTKEYFRAME_H__

#include "2d/CCAction.h"
#include "SCEffectElement.h"
#include "tinyxml2/tinyxml2.h"

enum
{
	EFT_KEYFRAME_ALPHA,
	EFT_KEYFRAME_SCALE,
	EFT_KEYFRAME_ROTATION,
	EFT_KEYFRAME_COLOR,
	EFT_KEYFRAME_POSITION,
};

class SCEffectKeyframeControl
{
public:
	SCEffectKeyframeControl(int type) : m_iType(type) {}
	virtual ~SCEffectKeyframeControl() {}

	virtual bool loadData(tinyxml2::XMLNode* xmlNode, int startFrame) = 0;
	virtual cocos2d::ActionInterval* getAction() const = 0;

	int getType() const { return m_iType; }

protected:
	int m_iType;
};

class SCEffectKeyframeData
{
	typedef std::vector<SCEffectKeyframeControl*> KeyframeControlList;

public:
	SCEffectKeyframeData();
	virtual ~SCEffectKeyframeData();

	void loadKeyframeData(tinyxml2::XMLNode* xmlNode, int startFrame);
	void runKeyframeAction(SCEffectElement* pElement);

protected:
	KeyframeControlList m_keyframes;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_EFFECTKEYFRAME_H__