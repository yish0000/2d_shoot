/*
* ------------------------------------------------------------------------
*  Name:   SCUICustom.h
*  Desc:   游戏开始界面
*  Author: Yish
*  Date:   2015/8/20
* ------------------------------------------------------------------------
*/

#ifndef __SC_UICUSTOM_H__
#define __SC_UICUSTOM_H__

#include "SCUIBase.h"

class SCUICustom : public SCUIBase
{
public:
	SCUICustom(const std::string& name, const std::string& filename);
	virtual ~SCUICustom();

	virtual bool init();
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UICUSTOM_H__