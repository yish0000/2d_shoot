/*
 * ------------------------------------------------------------------------
 *  Name:   SCComSprite.h
 *  Desc:   2D精灵组件
 *  Author: Yish
 *  Date:   2015/7/29
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COMSPRITE_H__
#define __SC_COMSPRITE_H__

#include "SCComponentBase.h"

class SCComSprite : public SCComponentBase
{
public:
	SCComSprite(const std::string& spriteName);
	virtual ~SCComSprite();

	virtual bool init();
	virtual void update(float dt);

	void setImageName(const char* filename);
	const std::string& getImageName() const { return m_sFilename; }

	void refreshSprite();

	// 设置缩放
	void setScaleX(float x);
	void setScaleY(float y);
	void setScale(float x, float y);

	// 设置透明
	void fadeTo(int opacity, float fTime);

	cocos2d::Sprite* getSprite() { return m_pSprite; }

protected:
	std::string m_sFilename;
	cocos2d::Sprite* m_pSprite;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMSPRITE_H__