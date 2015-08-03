/*
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
	// 添加引用
	void retain();
	// 释放引用
	void release();
};

///////////////////////////////////////////////////////////////////////////
// SOME MACROS

#define DEFINE_TEMPL(tmpl) struct tmpl : public DATA_TEMPL_BASE
#define TEMPL_ENCODE(attrib) stream.push(#attrib, attrib)
#define TEMPL_DECODE(attrib) stream.pop(#attrib, attrib)

///////////////////////////////////////////////////////////////////////////

/** 数据模板类型
*/
enum SC_DATA_TYPE
{
	DT_INVALID = 0,

    DT_WORLD_ESSENCE,			// 世界模板
	DT_NPC_ESSENCE,				// NPC模板
    DT_BULLET_ESSENCE,          // 子弹模板
};

///////////////////////////////////////////////////////////////////////////
// NPC模板

DEFINE_TEMPL(NPC_ESSENCE)
{
    std::string res_path;
    float scale;
	int max_hp;
	int move_speed;
	int jump_heigh;
	int atk_mode;
	int atk_interval;
    int bullet_id;

	NPC_ESSENCE() : scale(1.0),max_hp(100), move_speed(0), jump_heigh(100),atk_mode(1), atk_interval(1000), bullet_id(-1) {}

	void encode(scnet::JsonStream &stream) const
	{
        TEMPL_ENCODE(res_path);
        TEMPL_ENCODE(scale);
		TEMPL_ENCODE(max_hp);
		TEMPL_ENCODE(move_speed);
		TEMPL_ENCODE(jump_heigh);
		TEMPL_ENCODE(atk_mode);
		TEMPL_ENCODE(atk_interval);
		TEMPL_ENCODE(bullet_id);
	}

	void decode(const scnet::JsonStream &stream)
	{
        TEMPL_DECODE(res_path);
        TEMPL_DECODE(scale);
		TEMPL_DECODE(max_hp);
		TEMPL_DECODE(move_speed);
		TEMPL_DECODE(jump_heigh);
		TEMPL_DECODE(atk_mode);
		TEMPL_DECODE(atk_interval);
		TEMPL_DECODE(bullet_id);
	}
};

DEFINE_TEMPL(BULLET_ESSENCE)
{
    std::string res_path;
    float scale;
    int move_speed;
    int atk_max;
    int atk_min;

    BULLET_ESSENCE() : scale(1.0), move_speed(0), atk_min(0), atk_max(0) {}

    void encode(scnet::JsonStream &stream) const
    {
        TEMPL_ENCODE(res_path);
        TEMPL_ENCODE(scale);
        TEMPL_ENCODE(move_speed);
        TEMPL_ENCODE(atk_max);
        TEMPL_ENCODE(atk_min);
    }

    void decode(const scnet::JsonStream &stream)
    {
        TEMPL_DECODE(res_path);
        TEMPL_DECODE(scale);
        TEMPL_DECODE(move_speed);
        TEMPL_DECODE(atk_max);
        TEMPL_DECODE(atk_min);
    }
};
///////////////////////////////////////////////////////////////////////////
// 世界模板

DEFINE_TEMPL(WORLD_ESSENCE)
{
	std::string map_path;
	std::string back_music;

	WORLD_ESSENCE() {}

	void encode(scnet::JsonStream &stream) const
	{
		TEMPL_ENCODE(map_path);
		TEMPL_ENCODE(back_music);
	}

	void decode(const scnet::JsonStream &stream)
	{
		TEMPL_DECODE(map_path);
		TEMPL_DECODE(back_music);
	}
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_DATATYPES_H__