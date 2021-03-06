﻿/*
 * ------------------------------------------------------------------------
 *  Name:   SCJoystickBase.cpp
 *  Desc:   手柄对象
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "SCJoystickBase.h"
#include "UI/SCUIModule.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;

static const float JOYSTICK_RADIUS = 45.0f;

SCJoystickBase::SCJoystickBase(const std::string& back_img, const std::string& center_img)
	: m_sJoystickBack(back_img), m_sJoystickCenter(center_img), m_pSpriteBack(NULL), m_pSpriteCenter(NULL)
	, m_fX(0.0f), m_fY(0.0f), m_fPosX(0.0f), m_fPosY(0.0f), m_pRootNode(NULL)
{
	memset(m_bKeystate, 0, sizeof(m_bKeystate));
}

SCJoystickBase::~SCJoystickBase()
{
}

bool SCJoystickBase::init()
{
	if( !Node::init() )
		return false;

	m_fPosX = 120.0f * glb_getUIModule()->getUIScale();
	m_fPosY = 120.0f * glb_getUIModule()->getUIScale();

	// 创建摇杆节点
	m_pRootNode = Node::create();
	m_pRootNode->setPosition(m_fPosX, m_fPosY);
	m_pRootNode->setScale(glb_getUIModule()->getUIScale());
	addChild(m_pRootNode);

	// 摇杆中心点
	m_pSpriteCenter = Sprite::create(m_sJoystickCenter);
	m_pSpriteCenter->setAnchorPoint(Point(0.5f, 0.5f));
	m_pRootNode->addChild(m_pSpriteCenter);

	// 摇杆背景
	m_pSpriteBack = Sprite::create(m_sJoystickBack);
	m_pSpriteBack->setAnchorPoint(Point(0.5f, 0.5f));
	m_pRootNode->addChild(m_pSpriteBack);

	// WINDOWS平台注册按键事件
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	setKeyboardEnabled(true);
#endif

	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	return true;
}

bool SCJoystickBase::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if( touch->getLocation().x < 0 || touch->getLocation().x > m_fPosX * 2 ||
		touch->getLocation().y < 0 || touch->getLocation().y > m_fPosY * 2 )
		return true;

	Point pos = m_pRootNode->getPosition();
	float xx = touch->getLocation().x - pos.x;
	float yy = touch->getLocation().y - pos.y;

	if( xx * xx + yy * yy > JOYSTICK_RADIUS * JOYSTICK_RADIUS )
	{
		float degree = Point(xx, yy).getAngle();
		float px = JOYSTICK_RADIUS * cosf(degree);
		float py = JOYSTICK_RADIUS * sinf(degree);
		m_pSpriteCenter->setPosition(Point(px, py));
	}
	else
	{
		m_pSpriteCenter->setPosition(Point(xx, yy));
	}

	m_pSpriteBack->setScale(1.35f);

	float dx = fabs(xx);
	float dy = fabs(yy);
	float xDirection = 0.0f, yDirection = 0.0f;
	if( dx > dy || dy < 20 )
	{
		if( xx >= 0.0f )
			xDirection = 1.0f;
		else
			xDirection = -1;
		yDirection = 0.0f;
	}
	else
	{
		if( yy >= 0.0f )
			yDirection = 1.0f;
		else
			yDirection = -1.0f;
		xDirection = 0.0f;
	}

	onJoystickHandle(xDirection, yDirection);
	return true;
}

void SCJoystickBase::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if( touch->getLocation().x < 0 || touch->getLocation().x > m_fPosX * 2 ||
		touch->getLocation().y < 0 || touch->getLocation().y > m_fPosY * 2 )
		return;

	Point pos = m_pRootNode->getPosition();
	float xx = touch->getLocation().x - pos.x;
	float yy = touch->getLocation().y - pos.y;

	if( xx * xx + yy * yy > JOYSTICK_RADIUS * JOYSTICK_RADIUS )
	{
		float degree = Point(xx, yy).getAngle();
		float px = JOYSTICK_RADIUS * cosf(degree);
		float py = JOYSTICK_RADIUS * sinf(degree);
		m_pSpriteCenter->setPosition(Point(px, py));
	}
	else
	{
		m_pSpriteCenter->setPosition(Point(xx, yy));
	}

	float dx = fabs(xx);
	float dy = fabs(yy);
	float xDirection = 0.0f, yDirection = 0.0f;
	if( dx > dy || dy < 20 )
	{
		if( xx >= 0.0f )
			xDirection = 1.0f;
		else
			xDirection = -1;
		yDirection = 0.0f;
	}
	else
	{
		if( yy >= 0.0f )
			yDirection = 1.0f;
		else
			yDirection = -1.0f;
		xDirection = 0.0f;
	}

	onJoystickHandle(xDirection, yDirection);

}

void SCJoystickBase::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	m_pSpriteBack->runAction(ScaleTo::create(0.2f, 1.0f));
	m_pSpriteCenter->runAction(MoveTo::create(0.2f, Point(0.0f, 0.0f)));

	onJoystickHandle(0.0f, 0.0f);
}

void SCJoystickBase::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	m_pSpriteBack->runAction(ScaleTo::create(0.2f, 1.0f));
	m_pSpriteCenter->runAction(MoveTo::create(0.2f, Point(0.0f, 0.0f)));

	onJoystickHandle(0.0f, 0.0f);
}

void SCJoystickBase::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	float xDir = 0.0f;
	float yDir = 0.0f;

	if( keyCode != EventKeyboard::KeyCode::KEY_A && keyCode != EventKeyboard::KeyCode::KEY_LEFT_ARROW &&
		keyCode != EventKeyboard::KeyCode::KEY_S && keyCode != EventKeyboard::KeyCode::KEY_DOWN_ARROW &&
		keyCode != EventKeyboard::KeyCode::KEY_D && keyCode != EventKeyboard::KeyCode::KEY_RIGHT_ARROW &&
		keyCode != EventKeyboard::KeyCode::KEY_W && keyCode != EventKeyboard::KeyCode::KEY_UP_ARROW )
		return;

	m_bKeystate[(int)keyCode] = true;

	if( m_bKeystate[(int)EventKeyboard::KeyCode::KEY_W] || m_bKeystate[(int)EventKeyboard::KeyCode::KEY_UP_ARROW] )
		yDir = 1.0f;
	else if( m_bKeystate[(int)EventKeyboard::KeyCode::KEY_S] || m_bKeystate[(int)EventKeyboard::KeyCode::KEY_DOWN_ARROW] )
		yDir = -1.0f;

	if( m_bKeystate[(int)EventKeyboard::KeyCode::KEY_A] || m_bKeystate[(int)EventKeyboard::KeyCode::KEY_LEFT_ARROW] )
		xDir = -1.0f;
	else if( m_bKeystate[(int)EventKeyboard::KeyCode::KEY_D] || m_bKeystate[(int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW] )
		xDir = 1.0f;

	onJoystickHandle(xDir, yDir);
}

void SCJoystickBase::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	float xDir = 0.0f;
	float yDir = 0.0f;

	if( keyCode != EventKeyboard::KeyCode::KEY_A && keyCode != EventKeyboard::KeyCode::KEY_LEFT_ARROW &&
		keyCode != EventKeyboard::KeyCode::KEY_S && keyCode != EventKeyboard::KeyCode::KEY_DOWN_ARROW &&
		keyCode != EventKeyboard::KeyCode::KEY_D && keyCode != EventKeyboard::KeyCode::KEY_RIGHT_ARROW &&
		keyCode != EventKeyboard::KeyCode::KEY_W && keyCode != EventKeyboard::KeyCode::KEY_UP_ARROW )
		return;

	m_bKeystate[(int)keyCode] = false;

	if( m_bKeystate[(int)EventKeyboard::KeyCode::KEY_W] || m_bKeystate[(int)EventKeyboard::KeyCode::KEY_UP_ARROW] )
		yDir = 1.0f;
	else if( m_bKeystate[(int)EventKeyboard::KeyCode::KEY_S] || m_bKeystate[(int)EventKeyboard::KeyCode::KEY_DOWN_ARROW] )
		yDir = -1.0f;

	if( m_bKeystate[(int)EventKeyboard::KeyCode::KEY_A] || m_bKeystate[(int)EventKeyboard::KeyCode::KEY_LEFT_ARROW] )
		xDir = -1.0f;
	else if( m_bKeystate[(int)EventKeyboard::KeyCode::KEY_D] || m_bKeystate[(int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW] )
		xDir = 1.0f;

	onJoystickHandle(xDir, yDir);
}