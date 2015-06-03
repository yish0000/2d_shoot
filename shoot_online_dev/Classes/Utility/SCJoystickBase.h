/*
 * ------------------------------------------------------------------------
 *  Name:   SCJoystickBase.h
 *  Desc:   摇杆对象
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#ifndef __SC_JOYSTICKBASE_H__
#define __SC_JOYSTICKBASE_H__

#include "2d/CCLayer.h"

class SCJoystickBase : public cocos2d::Layer
{
public:
	SCJoystickBase(const std::string& back_img, const std::string& center_img);
	virtual ~SCJoystickBase();

    virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	cocos2d::Node* getRootNode() const { return m_pRootNode; }

	// 摇杆处理函数
	virtual void onJoystickHandle(float xDir, float yDir) = 0;

protected:
	std::string m_sJoystickBack;		// 摇杆背景图
	std::string m_sJoystickCenter;		// 摇杆中心点
	cocos2d::Node* m_pRootNode;
	float m_fX, m_fY;
	float m_fPosX, m_fPosY;
	cocos2d::Sprite* m_pSpriteBack;
	cocos2d::Sprite* m_pSpriteCenter;
	bool m_bKeystate[256];
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_JOYSTICKBASE_H__