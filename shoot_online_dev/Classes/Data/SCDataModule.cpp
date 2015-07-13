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
			deleteTemplate(it->second.tid);
			it = m_refs.erase(it);
		}
		else
			++it;
	}
}

void SCDataModule::clearResources()
{
	SCScopedMutex lock(m_mutex);

	std::unordered_map<int, DATA_TEMPL_BASE*>::iterator it = m_templs.begin();
	for (; it != m_templs.end(); ++it) delete it->second;

	m_templs.clear();
	m_refs.clear();
}

const void* SCDataModule::getTemplate(int tid, SC_DATA_TYPE dt)
{
	std::unordered_map<int, DATA_TEMPL_BASE*>::iterator it = m_templs.find(tid);
	if (it != m_templs.end())
	{
		m_refs[it->second].refCount++;
		return it->second;
	}

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

void SCDataModule::deleteTemplate(int tid)
{
	SCScopedMutex lock(m_mutex);

	if (m_templs.find(tid) != m_templs.end())
	{
		delete m_templs[tid];
		m_templs.erase(tid);
	}
	else
	{
		CCLOG("SCDataModule::deleteTemplate, template (%d) not exists!", tid);
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

void SCDataModule::addTemplate(int tid, DATA_TEMPL_BASE* data)
{
	SCScopedMutex lock(m_mutex);

	if (m_templs.find(tid) == m_templs.end())
	{
		CCLOG("SCDataModule::addTemplate, Template duplicated(%d)!", tid);
		return;
	}

	TemplStub stub;
	stub.tid = tid;
	stub.refCount = 1;
	m_refs[data] = stub;
	m_templs[tid] = data;
}