/*
 * ------------------------------------------------------------------------
 *  Name:   SCTickNum.cpp
 *  Desc:   设置一段数字的逐渐变化，并作出对应的回调
 *  Author: Yish
 *  Date:   2015/9/11
 * ------------------------------------------------------------------------
 */

#include "SCTickNum.h"
#include "cocos2d.h"

USING_NS_CC;

SCTickNum::SCTickNum()
	: m_fCurNum(0.0f), m_fDstNum(0.0f), m_fDeltaNum(0.0f), m_fElapsed(0.0f), m_fDuration(0.0f)
	, m_iExponential(0), m_pCBTick(nullptr), m_pCBEnd(nullptr)
{
}

void SCTickNum::start()
{
	stop();

	m_fElapsed = 0.0f;
	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

void SCTickNum::stop()
{
	Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}

void SCTickNum::update(float dt)
{
	m_fElapsed += dt;

	float fRate = clampf(m_fElapsed / m_fDuration, 0.0f, 1.0f);
	if (m_iExponential)
		fRate = (fRate == 1.0f) ? 1.0f : (1.0f - powf(2, -m_iExponential * fRate));

	m_fCurNum = m_fDstNum - m_fDeltaNum * (1.0f - fRate);

	if (m_pCBTick)
		m_pCBTick(this);
	if (fRate >= 1.0f)
	{
		stop();

		if (m_pCBEnd)
			m_pCBEnd(this);
	}
}