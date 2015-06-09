/*
 * ------------------------------------------------------------------------
 *  Name:   SCAudioElement.h
 *  Desc:   ÉùÒôÌØÐ§ÔªËØ
 *  Author: Yish
 *  Date:   2015/6/9
 * ------------------------------------------------------------------------
 */

#ifndef __SC_AUDIOELEMENT_H__
#define __SC_AUDIOELEMENT_H__

#include "SCEffectElement.h"

class SCAudioElementData;

class SCAudioElement : public SCEffectElement
{
public:
	SCAudioElement();
	virtual ~SCAudioElement();

	virtual bool init(SCEffectElementData* pData, bool stepAction);
	virtual void play();
	virtual void stop();
	virtual void pause();
	virtual void resume();
	virtual void resetPlay();

	virtual void runKeyFrameAction(cocos2d::Action* pAction, int type);

protected:
	SCAudioElementData* m_pData;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_AUDIOELEMENT_H__