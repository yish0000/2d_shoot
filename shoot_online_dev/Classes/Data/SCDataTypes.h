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

#define SC_INVALID_TID -1

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
	DT_PLAYER_ESSENCE,			// 玩家模板
	DT_NPC_ESSENCE,				// NPC模板
    DT_BULLET_ESSENCE,          // 子弹模板
    DT_NPCAI_ESSENCE,           // NPC AI模板
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
    int ai_mode;
    bool is_dispear;

	NPC_ESSENCE() : scale(1.0),max_hp(100), move_speed(0), jump_heigh(100),ai_mode(1),is_dispear(false) {}

	void encode(scnet::JsonStream &stream) const
	{
        TEMPL_ENCODE(res_path);
        TEMPL_ENCODE(scale);
		TEMPL_ENCODE(max_hp);
		TEMPL_ENCODE(move_speed);
		TEMPL_ENCODE(jump_heigh);
		TEMPL_ENCODE(ai_mode);
        TEMPL_ENCODE(is_dispear);
	}

	void decode(const scnet::JsonStream &stream)
	{
        TEMPL_DECODE(res_path);
        TEMPL_DECODE(scale);
		TEMPL_DECODE(max_hp);
		TEMPL_DECODE(move_speed);
		TEMPL_DECODE(jump_heigh);
		TEMPL_DECODE(ai_mode);
        TEMPL_DECODE(is_dispear);
	}
};

///////////////////////////////////////////////////////////////////////////
// 玩家模板

DEFINE_TEMPL(PLAYER_ESSENCE)
{
	std::string res_path;	// 角色模型
	float scale;			// 缩放
	int max_hp;				// 最大血量
	int move_speed;			// 移动速度
	int jump_height;		// 跳跃高度
	int orig_bullet_id;		// 初始子弹

	PLAYER_ESSENCE()
		: scale(1.0f), max_hp(100), move_speed(100), jump_height(100), orig_bullet_id(0)
	{
	}

	void encode(scnet::JsonStream &stream) const
	{
		TEMPL_ENCODE(res_path);
		TEMPL_ENCODE(scale);
		TEMPL_ENCODE(max_hp);
		TEMPL_ENCODE(move_speed);
		TEMPL_ENCODE(jump_height);
		TEMPL_ENCODE(orig_bullet_id);
	}

	void decode(const scnet::JsonStream &stream)
	{
		TEMPL_DECODE(res_path);
		TEMPL_DECODE(scale);
		TEMPL_DECODE(max_hp);
		TEMPL_DECODE(move_speed);
		TEMPL_DECODE(jump_height);
		TEMPL_DECODE(orig_bullet_id);
	}
};

///////////////////////////////////////////////////////////////////////////
// 子弹模板

DEFINE_TEMPL(BULLET_ESSENCE)
{
    std::string res_path;
    float scale;
    int move_speed;			// 子弹移动速度
    int atk_max;
    int atk_min;
	bool durative;			// 是否连发
	int atk_interval;		// 攻击频率(毫秒)

    BULLET_ESSENCE() : scale(1.0f), move_speed(0), atk_min(0), atk_max(0), durative(false), atk_interval(500) {}

    void encode(scnet::JsonStream &stream) const
    {
        TEMPL_ENCODE(res_path);
        TEMPL_ENCODE(scale);
        TEMPL_ENCODE(move_speed);
        TEMPL_ENCODE(atk_max);
        TEMPL_ENCODE(atk_min);
		TEMPL_ENCODE(durative);
		TEMPL_ENCODE(atk_interval);
    }

    void decode(const scnet::JsonStream &stream)
    {
        TEMPL_DECODE(res_path);
        TEMPL_DECODE(scale);
        TEMPL_DECODE(move_speed);
        TEMPL_DECODE(atk_max);
        TEMPL_DECODE(atk_min);
		TEMPL_DECODE(durative);
		TEMPL_DECODE(atk_interval);
    }
};

///////////////////////////////////////////////////////////////////////////
// NPC AI 模板

DEFINE_TEMPL(NPCAI_ESSENCE)
{
    int idle_mode;
    int atk_mode;
    int bullet_id;
    int atk_interval;

    NPCAI_ESSENCE() {}

    void encode(scnet::JsonStream &stream) const
    {
        TEMPL_ENCODE(idle_mode);
        TEMPL_ENCODE(atk_mode);
        TEMPL_ENCODE(bullet_id);
        TEMPL_ENCODE(atk_interval);
    }

    void decode(const scnet::JsonStream &stream)
    {
        TEMPL_DECODE(idle_mode);
        TEMPL_DECODE(atk_mode);
        TEMPL_DECODE(bullet_id);
        TEMPL_DECODE(atk_interval);
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