/*
 * ------------------------------------------------------------------------
 *  Name:   SCEffectElement.h
 *  Desc:   ÌØÐ§ÔªËØ
 *  Author: Yish
 *  Date:   2015/6/7
 * ------------------------------------------------------------------------
 */

#ifndef __SC_EFFECTELEMENT_H__
#define __SC_EFFECTELEMENT_H__

#include "2d/CCNode.h"

enum
{
	EFT_ELEMENT_UNKNOWN,

	EFT_ELEMENT_IMAGE,
	EFT_ELEMENT_PUPPET,
	EFT_ELEMENT_AUDIO,
};

class SCEffectElementData;

class SCEffectElement : public cocos2d::Node
{
public:
	SCEffectElement(int type) : m_iType(type), m_bResetPlay(false) {}
	virtual ~SCEffectElement() {}

	virtual bool init(SCEffectElementData* pData, bool stepAction) = 0;
	virtual void play() = 0;
	virtual void stop() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void resetPlay() = 0;
	virtual void preLoad() {}

	virtual void runKeyFrameAction(cocos2d::Action* pAction, int type) = 0;

	int getType() const { return m_iType; }

protected:
	int m_iType;
	bool m_bResetPlay;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_EFFECTELEMENT_H__