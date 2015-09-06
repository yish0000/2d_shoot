/*
 * ------------------------------------------------------------------------
 *  Name:   SCEffectData.cpp
 *  Desc:   特效数据
 *  Author: Yish
 *  Date:   2015/6/9
 * ------------------------------------------------------------------------
 */

#include "SCEffectData.h"
#include "SCEffectElement.h"
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"

USING_NS_CC;

SCEffectData::SCEffectData()
	: m_iFrameCount(0), m_iFrontBackDivide(0), m_iLoopCount(1)
	, m_iShakeEventFrame(-1), m_iShakeEventData(0)
{
}

SCEffectData::~SCEffectData()
{
}

bool SCEffectData::loadEffectData(const char* filename)
{
	if( !filename )
		return false;

	Data fileData = FileUtils::getInstance()->getDataFromFile(filename);

	tinyxml2::XMLDocument xmlDoc;
	if( xmlDoc.Parse((const char*)fileData.getBytes(), fileData.getSize()) != tinyxml2::XML_SUCCESS )
	{
		CCLOG("SCEffectData::loadEffectData, failed to load the effect file(%s)!", filename);
		return false;
	}

	tinyxml2::XMLElement* pRoot = xmlDoc.FirstChildElement();
	if( !pRoot )
	{
		CCLOG("SCEffectData::loadEffectData, failed to get the root node of this document (%s)!", filename);
		return false;
	}

	m_iLoopCount = -1;
	pRoot->QueryIntAttribute("loop", &m_iLoopCount);
	m_iFrontBackDivide = pRoot->IntAttribute("divide");
	float relBBox_x = pRoot->FloatAttribute("box_x");
	float relBBox_y = pRoot->FloatAttribute("box_y");
	float relBBox_w = pRoot->FloatAttribute("box_w");
	float relBBox_h = pRoot->FloatAttribute("box_h");
	float fps = pRoot->FloatAttribute("fps");
	m_iFrameCount = pRoot->IntAttribute("frames");

	tinyxml2::XMLElement* pChild = pRoot->FirstChildElement();
	while(pChild)
	{
		std::string name = pChild->Name();

		if( name == "events" )
		{
            
		}
		else if( name == "picani" )
		{
		}
		else if( name == "effect" )
		{
		}
		else if( name == "sound" )
		{
		}
		else
		{
			CCLOG("SCEffectData::loadEffectData, unknown element type(%s)!", name.c_str());
		}
		
		pChild = pChild->NextSiblingElement();
	}

	return true;
}