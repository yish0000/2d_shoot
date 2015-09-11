/*
 * ------------------------------------------------------------------------
 *  Name:   SCImageElement.h
 *  Desc:   ÖðÖ¡¶¯»­ÔªËØ
 *  Author: Yish
 *  Date:   2015/9/8
 * ------------------------------------------------------------------------
 */

#ifndef __SC_IMAGEELEMENT_H__
#define __SC_IMAGEELEMENT_H__

#include "SCEffectElement.h"

class SCImageSprite;
class SCImageElementData;

class SCImageElement : public SCEffectElement
{
public:
	SCImageElement();
	virtual ~SCImageElement();

	virtual bool init(SCEffectElementData* pData, bool stepAction);
	virtual void play();
	virtual void stop();
	virtual void pause();
	virtual void resume();
	virtual void resetPlay();
	virtual void preLoad();

	virtual void runKeyFrameAction(cocos2d::Action* pAction, int type);

protected:

};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_IMAGEELEMENT_H__