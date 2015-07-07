/*
 * ------------------------------------------------------------------------
 *  Name:   SCDataTypes.h
 *  Desc:   ����ģ������
 *  Author: Yish
 *  Date:   2015/7/1
 * ------------------------------------------------------------------------
 */

#ifndef __SC_DATATYPES_H__
#define __SC_DATATYPES_H__

#include "base/ccTypes.h"
#include "Network/netlib/stream/JsonStream.h"

/** ����ģ�����
*/
struct DATA_TEMPL_BASE : public scnet::JsonStreamObj
{
	int tid;			// ģ��ID
	std::string name;	// ģ������

	DATA_TEMPL_BASE() : tid(0) {}

	virtual void encode(scnet::JsonStream &stream) const
	{
		stream.push("tid", tid);
		stream.push("name", name);
	}

	virtual void decode(const scnet::JsonStream &stream)
	{
		stream.pop("tid", tid);
		stream.pop("name", name);
	}

	// �ͷ�����
	void release();
};

///////////////////////////////////////////////////////////////////////////
// SOME MACROS

#define DEFINE_TEMPL(tmpl) struct tmpl : public DATA_TEMPL_BASE
#define DEFINE_SUB_TEMPL(tmpl) struct tmpl : public scnet::JsonStreamObj
#define TEMPL_ENCODE(attrib) stream.push(#attrib, attrib)
#define TEMPL_DECODE(attrib) stream.pop(#attrib, attrib)

///////////////////////////////////////////////////////////////////////////

/** ����ģ������
*/
enum SC_DATA_TYPE
{
	DT_INVALID = 0,

	DT_NPC_ESSENCE,				// NPCģ��
	DT_WORLD_ESSENCE,			// ����ģ��
};

///////////////////////////////////////////////////////////////////////////
// NPCģ��

DEFINE_TEMPL(NPC_ESSENCE)
{
	DEFINE_SUB_TEMPL(equip_info)
	{
		std::string res_path;
		float scale;

		equip_info() : scale(1.0f) {}

		void encode(scnet::JsonStream &stream) const
		{
			TEMPL_ENCODE(res_path);
			TEMPL_ENCODE(scale);
		}

		void decode(const scnet::JsonStream &stream)
		{
			TEMPL_DECODE(res_path);
			TEMPL_DECODE(scale);
		}
	};

	int max_hp;
	int min_dc;
	int max_dc;
	int min_ac;
	int max_ac;

	equip_info equip_data;

	NPC_ESSENCE() : max_hp(100), min_dc(0), max_dc(100), min_ac(0), max_ac(100) {}

	void encode(scnet::JsonStream &stream) const
	{
		DATA_TEMPL_BASE::encode(stream);
		TEMPL_ENCODE(max_hp);
		TEMPL_ENCODE(min_dc);
		TEMPL_ENCODE(max_dc);
		TEMPL_ENCODE(min_ac);
		TEMPL_ENCODE(max_dc);
		TEMPL_ENCODE(equip_data);
	}

	void decode(const scnet::JsonStream &stream)
	{
		DATA_TEMPL_BASE::decode(stream);
		TEMPL_DECODE(max_hp);
		TEMPL_DECODE(min_dc);
		TEMPL_DECODE(max_dc);
		TEMPL_DECODE(min_ac);
		TEMPL_DECODE(max_dc);
		TEMPL_DECODE(equip_data);
	}
};

///////////////////////////////////////////////////////////////////////////
// ����ģ��

DEFINE_TEMPL(WORLD_ESSENCE)
{
	std::string map_path;

	WORLD_ESSENCE() {}

	void encode(scnet::JsonStream &stream) const
	{
		DATA_TEMPL_BASE::encode(stream);

		TEMPL_ENCODE(map_path);
	}

	void decode(const scnet::JsonStream &stream)
	{
		DATA_TEMPL_BASE::decode(stream);

		TEMPL_DECODE(map_path);
	}
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_DATATYPES_H__