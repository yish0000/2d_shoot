/*
 * ------------------------------------------------------------------------
 *  Name:   SCCounter.h
 *  Desc:   ¼ÆÊýÆ÷
 *  Author: Yish
 *  Date:   2015/6/2
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COUNTER_H__
#define __SC_COUNTER_H__

#include "base/ccTypes.h"

class SCCounter
{
public:
	SCCounter() : m_fCounter(0), m_fPeriod(0), m_bPause(false) {}

	void setPeriod(float period) { m_fPeriod = period; }
	float getPeriod() const { return m_fPeriod; }
	void setCounter(float counter) { m_fCounter = counter; }
	float getCounter() const { return m_fCounter; }
	bool isFull() const { return m_fCounter >= m_fPeriod; }
	void reset(bool full = false) { m_fCounter = full ? m_fPeriod : 0; }
	void setPause(bool pause) { m_bPause = pause; }
	bool isPause() const { return m_bPause; }

	bool incCounter(float fCounter)
	{
		if( !m_bPause )
			m_fCounter += fCounter;
		return m_fCounter >= m_fPeriod ? true : false;
	}

	void decCounter(float fCounter)
	{
		if( m_bPause )
			return;

		if( m_fCounter <= m_fCounter )
			m_fCounter = 0;
		else
			m_fCounter -= fCounter;
	}

protected:
	float m_fCounter;
	float m_fPeriod;
	bool m_bPause;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COUNTER_H__