/*
 * ------------------------------------------------------------------------
 *  Name:   SCComSprite.cpp
 *  Desc:   2D¾«Áé×é¼þ
 *  Author: Yish
 *  Date:   2015/7/29
 * ------------------------------------------------------------------------
 */

#include "SCComSprite.h"
#include "Game/SCObject.h"

USING_NS_CC;

SCComSprite::SCComSprite(const std::string& spriteName)
	: SCComponentBase(SC_COMPONENT_SPRITE), m_sFilename(spriteName), m_pSprite(NULL)
{
}

SCComSprite::~SCComSprite()
{
}

bool SCComSprite::init()
{
	m_pSprite = Sprite::create(m_sFilename);
	m_pSprite->setAnchorPoint(Point(0.5f, 0.5f));
	m_pGameObj->addChild(m_pSprite);
	return true;
}

void SCComSprite::update(float dt)
{
}

void SCComSprite::setImageName(const char* filename)
{
	if( m_sFilename != filename )
	{
		m_pSprite->setTexture(filename);
		m_sFilename = filename;
	}
}

void SCComSprite::refreshSprite()
{
	int dir = m_pGameObj->getFaceDirection();
	CCASSERT(dir == 1 || dir == -1, "Invalid face direction value!!");

	m_pSprite->setScaleX(m_pSprite->getScaleX() * dir);
}

void SCComSprite::setScale(float x, float y)
{
	m_pSprite->setScale(x, y);
}

void SCComSprite::setScaleX(float x)
{
	m_pSprite->setScaleX(x);
}

void SCComSprite::setScaleY(float y)
{
	m_pSprite->setScaleY(y);
}

void SCComSprite::fadeTo(int opacity, float fTime)
{
	m_pSprite->runAction(FadeTo::create(fTime, opacity));
}