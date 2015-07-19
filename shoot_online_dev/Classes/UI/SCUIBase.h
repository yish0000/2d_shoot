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

	// ����·��ȡһ��������ӿؼ�
	cocos2d::ui::Widget* getControlByPath(const char* path);
	// ��ȡһ��ָ���ڵ���ӿؼ�
	cocos2d::ui::Widget* getControlByPath(cocos2d::ui::Widget* pRoot, const char* path);
	// ����tag��ȡ�ӿؼ�
	cocos2d::ui::Widget* getControlByTag(int tag);

protected:
	std::string m_sFilename;				// ��������ļ�·��
	cocos2d::ui::Widget* m_pRootWidget;		// ������Ľڵ���
	UIAlignType m_alignType;

	// Get the pointer of specified control
	template <class T>
	void DDX_Control(T*& pControl, const char* szName, bool bRetain = false);
};

///////////////////////////////////////////////////////////////////////////
/// Inline Functions

template <class T>
void SCUIBase::DDX_Control(T*& pControl, const char* szName, bool bRetain)
{
	cocos2d::ui::Widget* p = getControlByPath(szName);
	if( p )
	{
		T* pCtrl = dynamic_cast<T*>(p);
		if( pCtrl )
		{
			pControl = pCtrl;
			if( bRetain ) pControl->retain();
		}
		else
			CCASSERT(false, "The control's type is invalid!");
	}
	else
	{
		CCASSERT(false, "Can't find the control!");
	}
}

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UIBASE_H__