/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIModule.cpp
 *  Desc:   UI模块
 *  Author: Yish
 *  Date:   2015/5/24
 * ------------------------------------------------------------------------
 */

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"

#include "SCUIBase.h"
#include "SCUIModule.h"
#include "Scene/SCSceneBase.h"
#include "Utility/SCUtilityFunc.h"
#include "Scene/SCSceneManager.h"
#include "Main/SCGame.h"

USING_NS_CC;

///////////////////////////////////////////////////////////////////////////

SCUIModule::SCUIModule()
	: SCModuleBase(MODULE_TYPE_UI), m_fUIScale(1.0f), m_iCurType(FRAME_UNKNOWN)
{
}

SCUIModule::~SCUIModule()
{
	clearResources();
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

	// 加载UI对齐数据
	if( !loadUIAlignData() )
	{
		CCLOG("SCUIModule::init, load the align data failed!");
		return false;
	}

	initUICreateFunc();
	initEventHandlers();
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
		if (pFrame->Attribute("parent"))
			info.parent_name = pFrame->Attribute("parent");
		if (pFrame->Attribute("z"))
			info.zOrder = pFrame->IntAttribute("z");
		if( pFrame->Attribute("modal") )
			info.modalDlg = pFrame->BoolAttribute("modal");
		m_UIMetas[info.name] = info;

		pFrame = pFrame->NextSiblingElement("frame");
	}

	return true;
}

static UIAlignType str2AlignType(const char* str)
{
	if( !strcmp(str, "left") )
		return UI_ALIGN_LEFT;
	else if( !strcmp(str, "top") )
		return UI_ALIGN_TOP;
	else if( !strcmp(str, "right") )
		return UI_ALIGN_RIGHT;
	else if( !strcmp(str, "bottom") )
		return UI_ALIGN_BOTTOM;
	else if( !strcmp(str, "left_top") )
		return UI_ALIGN_LEFT_TOP;
	else if( !strcmp(str, "left_middle") )
		return UI_ALIGN_LEFT_MIDDLE;
	else if( !strcmp(str, "left_bottom") )
		return UI_ALIGN_LEFT_BOTTOM;
	else if( !strcmp(str, "middle_top") )
		return UI_ALIGN_MIDDLE_TOP;
	else if( !strcmp(str, "center") )
		return UI_ALIGN_CENTER;
	else if( !strcmp(str, "middle_bottom") )
		return UI_ALIGN_MIDDLE_BOTTOM;
	else if( !strcmp(str, "right_top") )
		return UI_ALIGN_RIGHT_TOP;
	else if( !strcmp(str, "right_middle") )
		return UI_ALIGN_RIGHT_MIDDLE;
	else if( !strcmp(str, "right_bottom") )
		return UI_ALIGN_RIGHT_BOTTOM;
	else
		return UI_ALIGN_NONE;
}

bool SCUIModule::loadUIAlignData()
{
	std::string fileData = FileUtils::getInstance()->getStringFromFile("ui/uialign.xml");

	tinyxml2::XMLDocument xmlDoc;
	if (xmlDoc.Parse(fileData.c_str()) != tinyxml2::XML_SUCCESS)
	{
		CCLOG("SCUIModule::loadUIAlignData, parse the ui align data failed!");
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
		std::string frameName = pFrame->Attribute("name");

		if (m_UIAligns.find(frameName) != m_UIAligns.end())
		{
			CCLOG("SCUIModule, frame name duplicated! (%s)", frameName.c_str());
			return false;
		}

		m_UIAligns[frameName] = UIAlignList();

		tinyxml2::XMLElement* pObject = pFrame->FirstChildElement("object");
		while(pObject)
		{
			UIAlignInfo align;
			align.obj_path = pObject->Attribute("name");
			align.align = str2AlignType(pObject->Attribute("align"));
			if( pObject->Attribute("x") )
				align.pos.x = pObject->IntAttribute("x");
			if( pObject->Attribute("y") )
				align.pos.y = pObject->IntAttribute("y");
			m_UIAligns[frameName].push_back(align);
			pObject = pObject->NextSiblingElement("object");
		}

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
	// 销毁旧的界面
	for (UITable::iterator it = m_UITable.begin(); it != m_UITable.end(); ++it)
	{
		SCUIBase* pUI = it->second;
		if (pUI)
		{
			if( pUI->getParent() )
				pUI->removeFromParent();
			CC_SAFE_RELEASE(pUI);
		}
	}

	m_UITable.clear();
}

SCUIBase* SCUIModule::getUIFrame(const std::string& name)
{
	UITable::iterator it = m_UITable.find(name);
	if (it != m_UITable.end())
		return it->second;

	UIMetaInfoTable::iterator mit = m_UIMetas.find(name);
	if (mit == m_UIMetas.end())
	{
		CCLOG("SCUIModule::getUIFrame, cannot find the frame (%s)!", name.c_str());
		return NULL;
	}
	else
	{
		if (mit->second.type != m_iCurType && mit->second.type != FRAME_COMMON)
		{
			CCLOG("SCUIModule::getUIFrame, this frame is not active in this ui type! (%d)", m_iCurType);
			return NULL;
		}
	}

	UIMetaInfo& info = mit->second;
	SCUIBase* pUI = createUIFrame(info.name);
	if (!pUI)
	{
		CCLOG("SCUIModule::getUIFrame, create the specified frame failed! (%s)", info.name.c_str());
		return NULL;
	}

	if (!pUI->init())
	{
		delete pUI;
		CCLOG("SCUIModule::getUIFrame, initialize the specified frame failed! (%s)", info.name.c_str());
		return NULL;
	}

	m_UITable[info.name] = pUI;
	return pUI;
}

void SCUIModule::changeUIType(UIFrameType type)
{
	if (m_iCurType == type)
		return;

	// 销毁旧的界面
	for (UITable::iterator it = m_UITable.begin(); it != m_UITable.end(); ++it)
	{
		SCUIBase* pUI = it->second;
		if (pUI)
		{
			if( pUI->getParent() )
				pUI->removeFromParent();
			CC_SAFE_RELEASE(pUI);
		}
	}

	m_UITable.clear();

	m_iCurType = type;

	// 加载本类型中活动的界面
	for (UIMetaInfoTable::iterator nit = m_UIMetas.begin(); nit != m_UIMetas.end(); ++nit)
	{
		UIMetaInfo& info = nit->second;
		if (info.type == m_iCurType || info.type == FRAME_COMMON)
		{
			SCUIBase* pNewUI = getUIFrame(info.name);
			if (pNewUI)
			{
				if (info.visible)
				{
					if (!info.parent_name.empty())
					{
						SCUIBase* pParentUI = getUIFrame(info.parent_name);
						if (pParentUI)
							pParentUI->addChild(pNewUI, info.zOrder);
					}
					else
						getUILayer()->addChild(pNewUI, info.zOrder);
				}

				pNewUI->setVisible(info.visible);
			}
		}
	}
}

cocos2d::Layer* SCUIModule::getUILayer()
{
	SCSceneBase* pCurScene = SCSceneManager::getInstance().getCurScene();
	return pCurScene ? pCurScene->getUILayer() : NULL;
}

bool SCUIModule::isModalDialog(const std::string& name) const
{
	UIMetaInfoTable::const_iterator it = m_UIMetas.find(name);
	if( it != m_UIMetas.end() )
		return it->second.modalDlg;
	else
		return false;
}

const SCUIModule::UIAlignList* SCUIModule::getUIAlignList(const std::string& frameName) const
{
	UIAlignMap::const_iterator it = m_UIAligns.find(frameName);
	return it != m_UIAligns.end() ? &it->second : NULL;
}

const SCUIModule::UIAlignInfo* SCUIModule::getUIAlignInfo(const std::string& frameName, const std::string& obj_path) const
{
	UIAlignMap::const_iterator it = m_UIAligns.find(frameName);
	if( it != m_UIAligns.end() )
	{
		const UIAlignList& lst = it->second;
		for(size_t i=0; i<lst.size(); ++i)
		{
			if( lst[i].obj_path == obj_path )
				return &lst[i];
		}
	}

	return NULL;
}

const SCUIModule::UIMetaInfo* SCUIModule::getUIMetaInfo(const std::string& name) const
{
	UIMetaInfoTable::const_iterator it = m_UIMetas.find(name);
	return it != m_UIMetas.end() ? &it->second : NULL;
}

///////////////////////////////////////////////////////////////////////////
// EVENT HANDLERS

void SCUIModule::initEventHandlers()
{
	REGISTER_EVENT_HANDLER(SC_EVENT_SWITCH_GAMESTATE, SCUIModule::onEventSwitchGameState);
	REGISTER_EVENT_HANDLER(SC_EVENT_STAGE_CLEAR, SCUIModule::onEventStageClear);
}

void SCUIModule::onEventSwitchGameState(SCEvent* pEvent)
{
	SCEventSwitchGameState* pSwitchState = dynamic_cast<SCEventSwitchGameState*>(pEvent);
	if (pSwitchState->m_iNewState == SCGame::GS_LOADING)
		changeUIType(FRAME_LOADING);
	else if (pSwitchState->m_iNewState == SCGame::GS_LOGIN)
		changeUIType(FRAME_LOGIN);
	else if (pSwitchState->m_iNewState == SCGame::GS_MAIN)
		changeUIType(FRAME_MAIN);
	else if (pSwitchState->m_iNewState == SCGame::GS_BATTLE)
		changeUIType(FRAME_BATTLE);
}

void SCUIModule::onEventStageClear(SCEvent* pEvent)
{
	// 由于没有通关界面，临时代码 退出关卡状态
	Sequence* pAction = Sequence::create(DelayTime::create(5.0f), CallFunc::create(std::bind([&] {
		SCGame::getInstance().changeGameState(SCGame::GS_MAIN);
	})), nullptr);
	getUILayer()->runAction(pAction);
}