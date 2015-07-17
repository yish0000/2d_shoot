/*
 * ------------------------------------------------------------------------
 *  Name:   SCUITypes.h
 *  Desc:   UI模块相关类型
 *  Author: Yish
 *  Date:   2015/7/14
 * ------------------------------------------------------------------------
 */

#ifndef __SC_UITYPES_H__
#define __SC_UITYPES_H__

/** 界面类型
*/
enum UIFrameType
{
	FRAME_COMMON,
	FRAME_LOGIN,
	FRAME_LOADING,
	FRAME_MAIN,
	FRAME_BATTLE,
};

/** 界面对齐方式
*/
enum UIAlignType
{
	UI_ALIGN_LEFT_TOP,
	UI_ALIGN_LEFT_MIDDLE,
	UI_ALIGN_LEFT_BOTTOM,
	UI_ALIGN_RIGHT_TOP,
	UI_ALIGN_RIGHT_MIDDLE,
	UI_ALIGN_RIGHT_BOTTOM,
	UI_ALIGN_MIDDLE_TOP,
	UI_ALIGN_CENTER,
	UI_ALIGN_MIDDLE_BOTTOM,
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UITYPES_H__