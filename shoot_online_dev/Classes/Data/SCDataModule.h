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

/** 数据模块
*/
class SCDataModule : public SCModuleBase
{
	struct TemplStub
	{
		int refCount;
		int tid;
	};
	typedef std::unordered_map<const void*, TemplStub> TemplRefMap;

	friend struct DATA_TEMPL_BASE;

public:
	SCDataModule();
	virtual ~SCDataModule();

	virtual bool init();
	virtual void update(float dt);

	void clearResources();

	// 获取模板数据
	const void* getTemplate(int tid, SC_DATA_TYPE dt);

	// 添加模板数据
	void addTemplate(int tid, DATA_TEMPL_BASE* data);

protected:
	SCMutex m_mutex;
	std::unordered_map<int, DATA_TEMPL_BASE*> m_templs;
	TemplRefMap m_refs;		// 引用管理
	SCCounter m_cntGC;		// 垃圾处理

	// 删除模板数据
	void deleteTemplate(int tid);
	// 添加指定模板的引用
	void retainTemplate(DATA_TEMPL_BASE* ptr);
	// 释放指定模板的引用
	void releaseTemplate(DATA_TEMPL_BASE* ptr);
	// 垃圾处理
	void garbageCollect();
};

extern SCDataModule* g_pDataModule;

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_DATAMODULE_H__