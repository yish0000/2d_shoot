﻿/*
 * ------------------------------------------------------------------------
 *  Name:   SCDataTypes.h
 *  Desc:   数据模板类型
 *  Author: Yish
 *  Date:   2015/7/1
 * ------------------------------------------------------------------------
 */

#ifndef __SC_DATATYPES_H__
#define __SC_DATATYPES_H__

#include "base/ccTypes.h"
#include "Network/netlib/stream/JsonStream.h"

/** 数据模板基类
*/
struct DATA_TEMPL_BASE : public scnet::JsonStreamObj
{
	int tid;			// 模板ID
	std::string name;	// 模板名字

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

	// 释放引用
	void release();
};

///////////////////////////////////////////////////////////////////////////
// SOME MACROS

#define DEFINE_TEMPL(tmpl) struct tmpl : public DATA_TEMPL_BASE
#define DEFINE_SUB_TEMPL(tmpl) struct tmpl : public scnet::JsonStreamObj
#define TEMPL_ENCODE(attrib) stream.push(#attrib, attrib)
#define TEMPL_DECODE(attrib) stream.pop(#attrib, attrib)

///////////////////////////////////////////////////////////////////////////

/** 数据模板类型
*/
enum SC_DATA_TYPE
{
	DT_INVALID = 0,

	DT_NPC_ESSENCE,				// NPC模板
	DT_WORLD_ESSENCE,			// 世界模板
};

///////////////////////////////////////////////////////////////////////////
// NPC模板

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
	int move_speed;
	int jump_heigh;
	int atk_mode;
	int atk_interval;
    int bullet_id;

	NPC_ESSENCE() : max_hp(100), move_speed(0), jump_heigh(100),atk_mode(1), atk_interval(1000), bullet_id(-1) {}

	void encode(scnet::JsonStream &stream) const
	{
		DATA_TEMPL_BASE::encode(stream);
		TEMPL_ENCODE(max_hp);
		TEMPL_ENCODE(move_speed);
		TEMPL_ENCODE(jump_heigh);
		TEMPL_ENCODE(atk_mode);
		TEMPL_ENCODE(atk_interval);
		TEMPL_ENCODE(bullet_id);
	}

	void decode(const scnet::JsonStream &stream)
	{
		DATA_TEMPL_BASE::decode(stream);
		TEMPL_DECODE(max_hp);
		TEMPL_DECODE(move_speed);
		TEMPL_DECODE(jump_heigh);
		TEMPL_DECODE(atk_mode);
		TEMPL_DECODE(atk_interval);
		TEMPL_DECODE(bullet_id);
	}
};

///////////////////////////////////////////////////////////////////////////
// 世界模板

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