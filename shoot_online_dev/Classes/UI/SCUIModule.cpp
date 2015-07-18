/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIModule.cpp
 *  Desc:   UI模块
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "SCUIBase.h"
#include "SCUIModule.h"
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"

USING_NS_CC;

///////////////////////////////////////////////////////////////////////////

SCUIModule::SCUIModule()
	: SCModuleBase(MODULE_TYPE_UI), m_fUIScale(1.0f)
{
}

SCUIModule::~SCUIModule()
{
}

bool SCUIModule::init()
{
    if( !SCModuleBase::init() )
        return false;
    
	// 加载UI元数据
	if (!loadUIMetaData())
	{
		CCLOG("SCUIModule::init, load the meta data failed!");
		return false;
	}

    return true;
}

bool SCUIModule::loadUIMetaData()
{
	std::string fileData = FileUtils::getInstance()->getStringFromFile("ui/uimeta.xml");

	tinyxml2::XMLDocument xmlDoc;
	if (xmlDoc.Parse(fileData.c_str()) != tinyxml2::XML_SUCCESS)
	{
		CCLOG("SCUIModule::loadUIMetaData, parse the ui meta data failed!");
		return false;
	}

	tinyxml2::XMLElement* pRoot = xmlDoc.FirstChildElement();
	if (!pRoot)
	{
		CCLOG("SCUIModule, failed to get the root node of this document!");
		return false;
	}

	tinyxml2::XMLElement* pFrame = pRoot->FirstChildElement("frame");
	while (pFrame)
	{
		UIMetaInfo info;
		info.name = pFrame->Attribute("name");

		if (m_UIMetas.find(info.name) != m_UIMetas.end())
		{
			CCLOG("SCUIModule, frame name duplicated! (%s)", info.name.c_str());
			return false;
		}

		info.filename = pFrame->Attribute("filename");
		info.type = (UIFrameType)pFrame->IntAttribute("type");
		info.visible = pFrame->BoolAttribute("visible");
		info.parent_name = pFrame->Attribute("parent");
		info.zOrder = pFrame->IntAttribute("z");
		m_UIMetas[info.name] = info;

		pFrame = pFrame->NextSiblingElement("frame");
	}

	return true;
}

void SCUIModule::update(float dt)
{
    SCModuleBase::update(dt);
    
	UITable::const_iterator it = m_UITable.begin();
	for (; it != m_UITable.end(); ++it)
	{
		SCUIBase* pFrame = it->second;
		if (pFrame->isVisible())
			pFrame->update(dt);
	}
}

void SCUIModule::clearResources()
{
}

SCUIBase* SCUIModule::getUIFrame(const std::string& name)
{
	UIMetaInfoTable::iterator it = m_UIMetas.find(name);
	if (it == m_UIMetas.end())
	{
		CCLOG("SCUIModule::getUIFrame, cannot find the frame (%s)!", name.c_str());
		return NULL;
	}

	UIMetaInfo& info = it->second;
	return NULL;
}