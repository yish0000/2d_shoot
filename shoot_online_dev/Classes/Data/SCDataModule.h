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

	// ��ȡģ������
	const void* getTemplate(SC_DATA_TYPE dt, int tid);

	// �ͷ�ָ��ģ�������
	void releaseTemplate(DATA_TEMPL_BASE* ptr);

protected:
	SCMutex m_mutex;
	std::unordered_map<int, NPC_ESSENCE*> m_npcs;
	std::unordered_map<int, WORLD_ESSENCE*> m_worlds;
	TemplRefMap m_refs;		// ���ù���
	SCCounter m_cntGC;		// ��������

	// ���ģ������
	void addTemplate(int tid, NPC_ESSENCE* data);
	void addTemplate(int tid, WORLD_ESSENCE* data);

	// ��ȡָ�����͵�ģ��
	NPC_ESSENCE* getNPCEssence(int tid);
	WORLD_ESSENCE* getWorldEssence(int tid);

	// ɾ��ģ������
	void deleteTemplate(int tid, SC_DATA_TYPE dt);

	void garbageCollect();
};

extern SCDataModule* g_pDataModule;

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_DATAMODULE_H__