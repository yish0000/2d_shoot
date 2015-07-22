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
		int tid;
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
	const void* getTemplate(int tid, SC_DATA_TYPE dt);

	// 释放指定模板的引用
	void releaseTemplate(DATA_TEMPL_BASE* ptr);

    static SCDataModule* glb_getDataModule()
    {
        //随便鸡巴写了个
        static SCDataModule instance;
        return &instance;
    }

protected:
	SCMutex m_mutex;
	std::unordered_map<int, DATA_TEMPL_BASE*> m_templs;
	TemplRefMap m_refs;		// 引用管理
	SCCounter m_cntGC;		// 垃圾处理

	// 添加模板数据
	void addTemplate(int tid, DATA_TEMPL_BASE* data);

	// 获取指定类型的模板
	NPC_ESSENCE* getNPCEssence(int tid);
	WORLD_ESSENCE* getWorldEssence(int tid);

	// 删除模板数据
	void deleteTemplate(int tid);

	void garbageCollect();


};

extern SCDataModule* g_pDataModule;

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_DATAMODULE_H__