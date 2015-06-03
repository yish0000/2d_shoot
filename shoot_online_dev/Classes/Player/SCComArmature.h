/*
 * ------------------------------------------------------------------------
 *  Name:   SCComArmature.h
 *  Desc:   �����������
 *  Author: Yish
 *  Date:   2015/6/3
 * ------------------------------------------------------------------------
 */

#ifndef __SC_COMARMATURE_H__
#define __SC_COMARMATURE_H__

#include "SCComponentBase.h"
#include "cocostudio/CCArmature.h"

class SCComArmature : public SCComponentBase
{
public:
	SCComArmature(const std::string& res_name);
	virtual ~SCComArmature();

	virtual bool init();
	virtual void update(float dt);

	// ����ָ���Ķ���
	void playAnimation(const char* name, bool bLoop);
	void pauseAnimation();
	void resumeAnimation();

	// ˢ��ģ��
	void refreshArmature();

	// ����͸��
	void fadeTo(int opacity, float fTime);

	const std::string& getResName() const { return m_sResName; }
	cocostudio::Armature* getArmature() { return m_pArmature; }

protected:
	std::string m_sResName;
	cocostudio::Armature* m_pArmature;
	cocostudio::ArmatureAnimation* m_pAnimation;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMARMATURE_H__