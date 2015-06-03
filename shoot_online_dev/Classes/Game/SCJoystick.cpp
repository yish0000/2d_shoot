/*
 * ------------------------------------------------------------------------
 *  Name:   SCJoystick.cpp
 *  Desc:   手柄对象
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "SCJoystick.h"
#include "UI/UIModule.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;

static const float JOYSTICK_RADIUS = 45.0f;

SCJoystick::SCJoystick(const std::string& back_img, const std::string& center_img)
	: m_sJoystickBack(back_img), m_sJoystickCenter(center_img), m_pSpriteBack(NULL), m_pSpriteCenter(NULL)
	, m_fX(0.0f), m_fY(0.0f), m_fPosX(0.0f), m_fPosY(0.0f), m_pRootNode(NULL)
{
}

SCJoystick::~SCJoystick()
{
}

SCJoystick* SCJoystick::create(const std::string &back_img, const std::string &center_img)
{
    SCJoystick* pJoystick = new SCJoystick(back_img, center_img);
    if( pJoystick && pJoystick->init() )
    {
        pJoystick->autorelease();
        return pJoystick;
    }
    else
    {
        delete pJoystick;
        pJoystick = NULL;
        return NULL;
    }
}

bool SCJoystick::init()
{
	if( !Node::init() )
		return false;

	m_fPosY = 150.0f * glb_getUIModule()->getUIScale();
	m_fPosY = 150.0f * glb_getUIModule()->getUIScale();

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
	setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
	return true;
}

bool SCJoystick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Point pos = m_pRootNode->getPosition();
	float xx = pos.x - touch->getLocation().x;
	float yy = pos.y - touch->getLocation().y;

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
	return true;
}

void SCJoystick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Point pos = m_pRootNode->getPosition();
	float xx = pos.x - touch->getLocation().x;
	float yy = pos.y - touch->getLocation().y;

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
}

void SCJoystick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	m_pSpriteBack->runAction(ScaleTo::create(0.2f, 1.0f));
	m_pSpriteCenter->runAction(MoveTo::create(0.2f, Point(0.0f, 0.0f)));
}

void SCJoystick::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	m_pSpriteBack->runAction(ScaleTo::create(0.2f, 1.0f));
	m_pSpriteCenter->runAction(MoveTo::create(0.2f, Point(0.0f, 0.0f)));
}

void SCJoystick::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
}

void SCJoystick::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}