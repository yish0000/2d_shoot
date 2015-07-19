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

	addChild(m_pRootWidget);
	return true;
}

void SCUIBase::update(float dt)
{
	Node::update(dt);

}

void SCUIBase::setAlign(UIAlignType align)
{
	if (m_alignType != align)
	{

		m_alignType = align;
	}
}