/*
 * ------------------------------------------------------------------------
 *  Name:   SCTickNum.h
 *  Desc:   ����һ�����ֵ��𽥱仯����������Ӧ�Ļص�
 *  Author: Yish
 *  Date:   2015/9/11
 * ------------------------------------------------------------------------
 */

#ifndef __SC_TICKNUM_H__
#define __SC_TICKNUM_H__

#include <functional>
#include "base/ccTypes.h"

class SCTickNum
{
public:

	typedef std::function<void(SCTickNum*)> TICKNUM_CALLBACK;

public:
	SCTickNum();

	void start();
	void stop();
	void update(float dt);

	void setCurNumber(float fCur) { m_fCurNum = fCur; m_fDeltaNum = m_fDstNum - m_fCurNum; }
	void setDestNumber(float fDest) { m_fDeltaNum = fDest; m_fDeltaNum = m_fDstNum - m_fCurNum; }
	void setExponential(int iExponential) { m_iExponential = iExponential; }
	void setDuration(float fTime) { m_fDuration = fTime; }

	void setTickCallback(TICKNUM_CALLBACK pCB) { m_pCBTick = pCB; }
	void setEndCallback(TICKNUM_CALLBACK pCB) { m_pCBEnd = pCB; }

	float getCurNumber() const { return m_fCurNum; }
	float getDestNumber() const { return m_fDstNum; }
	float getDuration() const { return m_fDuration; }

protected:
	float m_fCurNum;
	float m_fDstNum;
	float m_fDeltaNum;
	float m_fDuration;			// ����ʱ��
	float m_fElapsed;
	int m_iExponential;			// �Ƿ�ָ�����仯
	TICKNUM_CALLBACK m_pCBTick;	// �仯�еĻص�
	TICKNUM_CALLBACK m_pCBEnd;	// �仯������Ļص�
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_TICKNUM_H__