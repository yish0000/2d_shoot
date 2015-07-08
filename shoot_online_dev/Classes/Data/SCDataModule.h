/*
 * ------------------------------------------------------------------------
 *  Name:   SCDataModule.h
 *  Desc:   ����ģ�������
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

	// ��ȡģ������
	const void* getTemplate(int tid, SC_DATA_TYPE dt);

	// �ͷ�ָ��ģ�������
	void releaseTemplate(DATA_TEMPL_BASE* ptr);

protected:
	SCMutex m_mutex;
	std::unordered_map<int, DATA_TEMPL_BASE*> m_templs;
	TemplRefMap m_refs;		// ���ù���
	SCCounter m_cntGC;		// ��������

	// ���ģ������
	void addTemplate(int tid, DATA_TEMPL_BASE* data);

	// ��ȡָ�����͵�ģ��
	NPC_ESSENCE* getNPCEssence(int tid);
	WORLD_ESSENCE* getWorldEssence(int tid);

	// ɾ��ģ������
	void deleteTemplate(int tid);

	void garbageCollect();
};

extern SCDataModule* g_pDataModule;

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_DATAMODULE_H__