/*
 * ------------------------------------------------------------------------
 *  Name:   SCDataModule.h
 *  Desc:   数据模板管理器
 *  Author: Yish
 *  Date:   2015/7/1
 * ------------------------------------------------------------------------
 */

#ifndef __SC_DATAMODULE_H__
#define __SC_DATAMODULE_H__

#include <unordered_map>
#include "Module/SCModuleBase.h"
#include "SCDataTypes.h"
#include "Utility/SCCounter.h"
#include "Common/SCThread.h"

class SCDataModule : public SCModuleBase
{
	struct TemplStub
	{
		int refCount;
		const DATA_TEMPL_BASE* pData;
		SC_DATA_TYPE dt;
	};
	typedef std::unordered_map<const void*, TemplStub> TemplRefMap;

public:
	SCDataModule();
	virtual ~SCDataModule();

	virtual bool init();
	virtual void update(float dt);

	void clearResources();

	// 获取模板数据
	const void* getTemplate(SC_DATA_TYPE dt, int tid);

	// 释放指定模板的引用
	void releaseTemplate(DATA_TEMPL_BASE* ptr);

protected:
	SCMutex m_mutex;
	std::unordered_map<int, NPC_ESSENCE*> m_npcs;
	std::unordered_map<int, WORLD_ESSENCE*> m_worlds;
	TemplRefMap m_refs;		// 引用管理
	SCCounter m_cntGC;		// 垃圾处理

	// 添加模板数据
	void addTemplate(int tid, NPC_ESSENCE* data);
	void addTemplate(int tid, WORLD_ESSENCE* data);

	// 获取指定类型的模板
	NPC_ESSENCE* getNPCEssence(int tid);
	WORLD_ESSENCE* getWorldEssence(int tid);

	// 删除模板数据
	void deleteTemplate(int tid, SC_DATA_TYPE dt);

	void garbageCollect();
};

extern SCDataModule* g_pDataModule;

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_DATAMODULE_H__