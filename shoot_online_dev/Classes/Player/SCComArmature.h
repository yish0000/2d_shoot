/*
 * ------------------------------------------------------------------------
 *  Name:   SCComArmature.h
 *  Desc:   ¹Ç÷À¶¯»­×é¼þ
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
	SCComArmature(SCObject* pObj, const std::string& res_name);
	virtual ~SCComArmature();

	virtual bool init();
	virtual void update(float dt);

protected:
	std::string m_sResName;
	cocostudio::Armature* m_pArmature;
	cocostudio::ArmatureAnimation* m_pAnimation;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_COMARMATURE_H__