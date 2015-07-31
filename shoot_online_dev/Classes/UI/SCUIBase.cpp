/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIBase.cpp
 *  Desc:   界面基类
 *  Author: Yish
 *  Date:   2015/6/25
 * ------------------------------------------------------------------------
 */

#include "SCUIBase.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;

SCUIBase::SCUIBase(const std::string& filename)
	: m_sFilename(filename), m_pRootWidget(NULL), m_alignType(UI_ALIGN_CENTER)
{
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
	m_pRootWidget->setTouchEnabled(false);
	addChild(m_pRootWidget);
	return true;
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

	setVisible(true);
	onShowUI();
}

void SCUIBase::hideUI()
{
	if (!isVisible())
		return;

	setVisible(false);
	onHideUI();
}

void SCUIBase::setWidgetAlign(const char* path, UIAlignType align, const cocos2d::Point& pos)
{
	Widget* pWidget = getControlByPath(path);
	if( !pWidget ) return;

	Point realPos(0, 0);
	Size winSize = Director::getInstance()->getWinSize();
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