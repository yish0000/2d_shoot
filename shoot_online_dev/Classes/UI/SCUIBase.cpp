/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIBase.cpp
 *  Desc:   界面基类
 *  Author: Yish
 *  Date:   2015/6/25
 * ------------------------------------------------------------------------
 */

#include "SCUIBase.h"
#include "SCUIModule.h"
#include "cocostudio/CocoStudio.h"
#include "Utility/SCUtilityFunc.h"

USING_NS_CC;
using namespace ui;

///////////////////////////////////////////////////////////////////////////
// 一些常量

static const float MODAL_LAYER_ENTER_TIME = 0.4f;
static const Color4B MODAL_LAYER_COLOR(0, 0, 0, 60);

///////////////////////////////////////////////////////////////////////////

SCUIBase::SCUIBase(const std::string& name, const std::string& filename)
	: m_sFilename(filename), m_pRootWidget(NULL), m_pLayerColor(NULL)
{
	setName(name);
	m_pUIModule = glb_getUIModule();
}

SCUIBase::~SCUIBase()
{
}

bool SCUIBase::init()
{
	if (!Node::init())
		return false;

	m_pRootWidget = cocostudio::GUIReader::getInstance()->widgetFromBinaryFile(m_sFilename.c_str());
	if (!m_pRootWidget)
	{
		CCASSERT(0, "");
		CCLOGERROR("SCUIBase::init, failed to load the uifile (%s)!", m_sFilename.c_str());
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	m_pRootWidget->setContentSize(winSize);
	alignControls();
	if( !m_pUIModule->isModalDialog(getName()) )
		m_pRootWidget->setTouchEnabled(false);
	else
	{
		m_pLayerColor = LayerColor::create(MODAL_LAYER_COLOR);
		addChild(m_pLayerColor);
	}

	addChild(m_pRootWidget);
	return true;
}

void SCUIBase::alignControls()
{
	const SCUIModule::UIAlignList* pAlignList = m_pUIModule->getUIAlignList(getName());
	if( !pAlignList ) return;

	SCUIModule::UIAlignList::const_iterator it = pAlignList->begin();
	for(; it != pAlignList->end(); ++it)
	{
		setWidgetAlign(it->obj_path.c_str(), it->align, it->pos);
	}
}

void SCUIBase::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();

	if (isModalDialog())
	{
		int opacity = m_pLayerColor->getOpacity();
		m_pLayerColor->setOpacity(0);
		Action* darken = FadeTo::create(MODAL_LAYER_ENTER_TIME, opacity);
		m_pLayerColor->runAction(darken);
	}	
}

// Split the string
static void SplitString(const char* str, const char* sep, std::vector<std::string>& strList)
{
	CCASSERT(str && sep, "str and sep must not be null!!!");

	strList.clear();

	char temp[512];
	CCASSERT(strlen(str) < 512, "string to be splitted is too long!!!");
	strcpy(temp, str);

	char *pCur = temp, *p = NULL;
	while (true)
	{
		p = strstr(pCur, sep);
		if (p) *p = '\0';

		if (strlen(pCur) > 0)
			strList.push_back(pCur);
		if (!p) break;

		pCur = p + strlen(sep);
	}
}

cocos2d::ui::Widget* SCUIBase::getControlByPath(const char* path)
{
	return getControlByPath(m_pRootWidget, path);
}

cocos2d::ui::Widget* SCUIBase::getControlByPath(cocos2d::ui::Widget* pRoot, const char* path)
{
	if (!pRoot || !path) return NULL;

	std::vector<std::string> strList;
	SplitString(path, "/", strList);
	if (!strList.size()) return NULL;

	Widget* pCurNode = pRoot;
	for (std::vector<std::string>::iterator it = strList.begin(); it != strList.end(); ++it)
	{
		Widget* pChild = dynamic_cast<Widget*>(pCurNode->getChildByName(*it));
		if (!pChild) return NULL;
		pCurNode = pChild;
	}

	return pCurNode;
}

cocos2d::ui::Widget* SCUIBase::getControlByTag(int tag)
{
	return Helper::seekWidgetByTag(m_pRootWidget, tag);
}

void SCUIBase::update(float dt)
{
	Node::update(dt);

}

void SCUIBase::showUI()
{
	if (isVisible())
		return;

	if (!getParent())
	{
		const SCUIModule::UIMetaInfo* pMeta = m_pUIModule->getUIMetaInfo(getName());
		if (pMeta->parent_name.empty())
		{
			if (pMeta->zOrder == 0)
				m_pUIModule->getUILayer()->addChild(this);
			else
				m_pUIModule->getUILayer()->addChild(this, pMeta->zOrder);
		}
		else
		{
			SCUIBase* pParentUI = getUIFrame(pMeta->parent_name.c_str());
			if (pParentUI)
				pParentUI->addChild(this, pMeta->zOrder);
		}
	}

	setVisible(true);
	onShowUI();
}

void SCUIBase::hideUI()
{
	if (!isVisible())
		return;

	if (getParent())
		removeFromParent();

	setVisible(false);
	onHideUI();
}

void SCUIBase::setWidgetAlign(const char* path, UIAlignType align, const cocos2d::Point& pos)
{
	if( align == UI_ALIGN_NONE ) return;
	Widget* pWidget = getControlByPath(path);
	if( !pWidget ) return;

	Point realPos = pWidget->getPosition();
	Size winSize = m_pRootWidget->getContentSize();
	switch(align)
	{
	case UI_ALIGN_CENTER:
		realPos.setPoint(winSize.width / 2, winSize.height / 2);
		break;
	case UI_ALIGN_LEFT_BOTTOM:
		realPos.setPoint(0, 0);
		break;
	case UI_ALIGN_LEFT_MIDDLE:
		realPos.setPoint(0, winSize.height / 2);
		break;
	case UI_ALIGN_LEFT_TOP:
		realPos.setPoint(0, winSize.height);
		break;
	case UI_ALIGN_MIDDLE_TOP:
		realPos.setPoint(winSize.width / 2, winSize.height);
		break;
	case UI_ALIGN_MIDDLE_BOTTOM:
		realPos.setPoint(winSize.width / 2, 0);
		break;
	case UI_ALIGN_RIGHT_BOTTOM:
		realPos.setPoint(winSize.width, 0);
		break;
	case UI_ALIGN_RIGHT_MIDDLE:
		realPos.setPoint(winSize.width, winSize.height / 2);
		break;
	case UI_ALIGN_RIGHT_TOP:
		realPos.setPoint(winSize.width, winSize.height);
		break;
	case UI_ALIGN_TOP:
		realPos.y = winSize.height;
		break;
	case UI_ALIGN_LEFT:
		realPos.x = 0;
		break;
	case UI_ALIGN_BOTTOM:
		realPos.y = 0;
		break;
	case UI_ALIGN_RIGHT:
		realPos.x = winSize.width;
		break;
	}

	realPos += pos;

	if( pWidget->getParent() == m_pRootWidget )
		pWidget->setPosition(realPos);
	else
	{
		Node* pParent = pWidget->getParent();

		// 转换到父节点的空间
		Point posInParent = pParent->convertToNodeSpace(realPos);
		pWidget->setPosition(posInParent);
	}
}

bool SCUIBase::isModalDialog() const
{
	return m_pRootWidget->isTouchEnabled();
}

SCUIBase* SCUIBase::getUIFrame(const char* name)
{
	return m_pUIModule->getUIFrame(name);
}