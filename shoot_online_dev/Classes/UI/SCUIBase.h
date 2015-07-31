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

///////////////////////////////////////////////////////////////////////////

#define REGISTER_BUTTON_EVENT(name, selector) \
	{ \
		cocos2d::ui::Widget* pNode = getControlByPath(name); \
		if (pNode) \
			pNode->addTouchEventListener(CC_CALLBACK_2(selector, this)); \
		else \
			CCLOG("REGISTER_BUTTON_EVENT: Can't find the control for name(%s)", name); \
	}


///////////////////////////////////////////////////////////////////////////

class SCUIModule;

class SCUIBase : public cocos2d::Node
{
public:
	SCUIBase(const std::string& filename);
	virtual ~SCUIBase();

	virtual bool init();
	virtual void update(float dt);

	// ����·��ȡһ��������ӿؼ�
	cocos2d::ui::Widget* getControlByPath(const char* path);
	// ��ȡһ��ָ���ڵ���ӿؼ�
	cocos2d::ui::Widget* getControlByPath(cocos2d::ui::Widget* pRoot, const char* path);
	// ����tag��ȡ�ӿؼ�
	cocos2d::ui::Widget* getControlByTag(int tag);

	// ��ʾ����
	void showUI();
	// ���ؽ���
	void hideUI();

	// ���ÿؼ����뷽ʽ
	// path: ָ���ؼ���·��
	// align: ���뷽ʽ
	// pos: ���λ��
	void setWidgetAlign(const char* path, UIAlignType align, const cocos2d::Point& pos);

protected:
	std::string m_sFilename;				// ��������ļ�·��
	SCUIModule* m_pUIModule;				// UIģ���ָ��
	cocos2d::ui::Widget* m_pRootWidget;		// ������Ľڵ���

	// Get the pointer of specified control
	template <class T>
	void DDX_Control(T*& pControl, const char* szName, bool bRetain = false);

	virtual void onShowUI() {}
	virtual void onHideUI() {}
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