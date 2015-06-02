/*
 * ------------------------------------------------------------------------
 *  Name:   SCJoystick.h
 *  Desc:   摇杆对象
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#ifndef __SC_JOYSTICK_H__
#define __SC_JOYSTICK_H__

#include "2d/CCLayer.h"

class SCJoystick : public cocos2d::Layer
{
public:
	SCJoystick(const std::string& back_img, const std::string& center_img);
	virtual ~SCJoystick();

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	cocos2d::Node* getRootNode() const { return m_pRootNode; }

protected:
	std::string m_sJoystickBack;		// 摇杆背景图
	std::string m_sJoystickCenter;		// 摇杆中心点
	cocos2d::Node* m_pRootNode;
	float m_fX, m_fY;
	float m_fPosX, m_fPosY;
	cocos2d::Sprite* m_pSpriteBack;
	cocos2d::Sprite* m_pSpriteCenter;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_JOYSTICK_H__