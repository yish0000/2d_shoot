/*
 * ------------------------------------------------------------------------
 *  Name:   SCComArmature.h
 *  Desc:   骨骼动画组件
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

	// 播放指定的动画
	void playAnimation(const char* name, bool bLoop);
	void pauseAnimation();
	void resumeAnimation();

	// 刷新模型
	void refreshArmature();

	// 设置透明
	void fadeTo(int opacity, float fTime);

	// 获取当前播放的动画
	std::string getCurAnimName() const;

	const std::string& getResName() const { return m_sResName; }
	cocostudio::Armature* getArmature() { return m_pArmature; }

protected:
	std::string m_sResName;
	cocostudio::Armature* m_pArmature;
	cocostudio::ArmatureAnimation* m_pAnimation;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMARMATURE_H__