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
	void playAnimation(const char* name, bool bLoop, bool bRestart = true, const std::string& restoreAnim="");
	void pauseAnimation();
	void resumeAnimation();

	// 刷新模型
	void refreshArmature();

	// 设置缩放
	void setScaleX(float x);
	void setScaleY(float y);
	void setScale(float x, float y);
	void setScale(float scale);

	// 设置透明
	void fadeTo(int opacity, float fTime);

	// 设置模型的初始朝向
	void setInitFaceDir(int dir);
	// 获取模型的初始朝向
	int getInitFaceDir() const { return m_iInitFaceDir; }

	// 获取当前播放的动画
	std::string getCurAnimName() const;
	// 当前动画是否播放完毕
	bool isCurAnimComplete() const;

	// 获取指定骨骼的世界坐标
	bool getBoneWorldPos(const char* name, cocos2d::Point& pos);

	const std::string& getResName() const { return m_sResName; }
	cocostudio::Armature* getArmature() { return m_pArmature; }

protected:
	std::string m_sResName;
	cocostudio::Armature* m_pArmature;
	cocostudio::ArmatureAnimation* m_pAnimation;
	int m_iInitFaceDir;		// 初始朝向
	std::string m_sRestoreAnim;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMARMATURE_H__