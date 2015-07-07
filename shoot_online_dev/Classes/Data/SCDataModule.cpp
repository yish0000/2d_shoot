/*
 * ------------------------------------------------------------------------
 *  Name:   SCDataModule.cpp
 *  Desc:   模板数据管理模块
 *  Author: Yish
 *  Date:   2015/7/1
 * ------------------------------------------------------------------------
 */

#include "SCDataModule.h"
#include "cocos2d.h"

USING_NS_CC;

SCDataModule* g_pDataModule = NULL;

SCDataModule::SCDataModule() : SCModuleBase(MODULE_TYPE_DATA)
{
	m_cntGC.setPeriod(30.0f);	// 30秒清理一次垃圾
	m_cntGC.reset();

	g_pDataModule = this;
}

SCDataModule::~SCDataModule()
{
	clearResources();
	g_pDataModule = NULL;
}

bool SCDataModule::init()
{
	if (!SCModuleBase::init())
		return false;

	return true;
}

void SCDataModule::update(float dt)
{
	SCModuleBase::update(dt);

	if (m_cntGC.incCounter(dt))
	{
		garbageCollect();
		m_cntGC.reset();
	}
}

void SCDataModule::garbageCollect()
{
	SCScopedMutex lock(m_mutex);

	TemplRefMap::iterator it = m_refs.begin();
	while (it != m_refs.end())
	{
		if (it->second.refCount <= 0)
		{
			deleteTemplate(it->second.pData->tid, it->second.dt);
			it = m_refs.erase(it);
		}
		else
			++it;
	}
}

void SCDataModule::clearResources()
{
	SCScopedMutex lock(m_mutex);

	for (std::unordered_map<int, NPC_ESSENCE*>::iterator it = m_npcs.begin(); it != m_npcs.end(); ++it) delete it->second;
	for (std::unordered_map<int, WORLD_ESSENCE*>::iterator it = m_worlds.begin(); it != m_worlds.end(); ++it) delete it->second;

	m_npcs.clear();
	m_worlds.clear();
	m_refs.clear();
}

const void* SCDataModule::getTemplate(SC_DATA_TYPE dt, int tid)
{
	switch (dt)
	{
	case DT_NPC_ESSENCE:
		return getNPCEssence(tid);
	case DT_WORLD_ESSENCE:
		return getWorldEssence(tid);
	default:
		CCLOG("SCDataModule::getTemplate, unknown data type (%d, %d)!", (int)dt, tid);
		return NULL;
	}
}

static bool loadTemplateFromFile(DATA_TEMPL_BASE* pTempl, const char* filename)
{
	Json::Value rootNode;
	Json::Reader json;

	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		CCLOG("SCConfigs::load, load the config file failed! (%s)", filename);
		return false;
	}

	std::string content = FileUtils::getInstance()->getStringFromFile(filename);
	if (!json.parse(content, rootNode))
	{
		CCLOG("SCConfigs::load, parse the file content failed! (%s)", filename);
		return false;
	}

	// 添加新模板
	scnet::JsonStream stream(rootNode);
	stream.popRootObject(*pTempl);
	return true;
}

NPC_ESSENCE* SCDataModule::getNPCEssence(int tid)
{
	std::unordered_map<int, NPC_ESSENCE*>::iterator it = m_npcs.find(tid);
	if (it != m_npcs.end())
	{
		m_refs[it->second].refCount++;
		return it->second;
	}

	char szFile[260];
	sprintf(szFile, "Data/npc/%d.json", tid);

	NPC_ESSENCE* pTempl = new NPC_ESSENCE();
	if (!loadTemplateFromFile(pTempl, szFile))
	{
		delete pTempl;
		return NULL;
	}

	addTemplate(pTempl->tid, pTempl);
	return pTempl;
}

WORLD_ESSENCE* SCDataModule::getWorldEssence(int tid)
{
	std::unordered_map<int, WORLD_ESSENCE*>::iterator it = m_worlds.find(tid);
	if (it != m_worlds.end())
	{
		m_refs[it->second].refCount++;
		return it->second;
	}

	char szFile[260];
	sprintf(szFile, "Data/world/%d.json", szFile);

	WORLD_ESSENCE* pTempl = new WORLD_ESSENCE();
	if (!loadTemplateFromFile(pTempl, szFile))
	{
		delete pTempl;
		return NULL;
	}

	addTemplate(pTempl->tid, pTempl);
	return pTempl;
}

void SCDataModule::deleteTemplate(int tid, SC_DATA_TYPE dt)
{
	SCScopedMutex lock(m_mutex);

	switch (dt)
	{
	case DT_NPC_ESSENCE:
		if (m_npcs.find(tid) != m_npcs.end())
		{
			delete m_npcs[tid];
			m_npcs.erase(tid);
		}
		break;
	case DT_WORLD_ESSENCE:
		if (m_worlds.find(tid) != m_worlds.end())
		{
			delete m_worlds[tid];
			m_worlds.erase(tid);
		}
		break;
	default:
		CCLOG("SCDataModule::deleteTemplate, unknown data type (%d, %d)!", (int)dt, tid);
	}
}

void SCDataModule::releaseTemplate(DATA_TEMPL_BASE* ptr)
{
	SCScopedMutex lock(m_mutex);

	TemplRefMap::iterator it = m_refs.find(ptr);
	if (it == m_refs.end())
	{
		CCASSERT(0, "SCDataModule::releaseTemplate");
		CCLOG("SCDataModule::releaseTemplate, can't find the specified template pointer!");
		return;
	}

	if (it->second.refCount <= 0)
	{
		CCLOG("SCDataModule::releaseTemplate, failed to release, template reference has been 0!");
		return;
	}

	it->second.refCount--;
}

void SCDataModule::addTemplate(int tid, NPC_ESSENCE* data)
{
	SCScopedMutex lock(m_mutex);

	if (m_npcs.find(tid) == m_npcs.end())
	{
		CCLOG("SCDataModule::addTemplate, NPC_ESSENCE duplicated(%d)!", tid);
		return;
	}

	TemplStub stub;
	stub.pData = data;
	stub.refCount = 1;
	m_refs[data] = stub;
	m_npcs[tid] = data;
}

void SCDataModule::addTemplate(int tid, WORLD_ESSENCE* data)
{
	SCScopedMutex lock(m_mutex);

	if (m_worlds.find(tid) == m_worlds.end())
	{
		CCLOG("SCDataModule::addTemplate, WORLD_ESSENCE duplicated(%d)!", tid);
		return;
	}

	TemplStub stub;
	stub.pData = data;
	stub.refCount = 1;
	m_refs[data] = stub;
	m_worlds[tid] = data;
}