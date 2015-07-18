/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIBase.h
 *  Desc:   �������
 *  Author: Yish
 *  Date:   2015/6/25
 * ------------------------------------------------------------------------
 */

#ifndef __SC_UIBASE_H__
#define __SC_UIBASE_H__

#include "2d/CCNode.h"
#include "ui/CocosGUI.h"
#include "SCUITypes.h"

class SCUIBase : public cocos2d::Node
{
public:
	SCUIBase(const std::string& filename);
	virtual ~SCUIBase();

	virtual bool init();
	virtual void update(float dt);

	// ���뷽ʽ
	void setAlign(UIAlignType align);
	UIAlignType getAlign() const { return m_alignType; }

protected:
	std::string m_sFilename;				// ��������ļ�·��
	cocos2d::ui::Widget* m_pRootWidget;		// ������Ľڵ���
	UIAlignType m_alignType;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UIBASE_H__