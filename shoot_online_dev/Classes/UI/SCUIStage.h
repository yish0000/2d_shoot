/*
* ------------------------------------------------------------------------
*  Name:   SCUIStage.h
*  Desc:   游戏开始界面
*  Author: Yish
*  Date:   2015/8/20
* ------------------------------------------------------------------------
*/

#ifndef __SC_UISTAGE_H__
#define __SC_UISTAGE_H__

#include "SCUIBase.h"

class SCUIStage : public SCUIBase
{
public:
	SCUIStage(const std::string& name, const std::string& filename);
	virtual ~SCUIStage();

	virtual bool init();
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UISTAGE_H__