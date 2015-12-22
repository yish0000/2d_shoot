/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIOption.h
 *  Desc:   游戏配置界面
 *  Author: Yish
 *  Date:   2015/8/20
 * ------------------------------------------------------------------------
 */

#ifndef __SC_UIOPTION_H__
#define __SC_UIOPTION_H__

#include "SCUIBase.h"

class SCUIOption : public SCUIBase
{
public:
	SCUIOption(const std::string& name, const std::string& filename);
	virtual ~SCUIOption();

	virtual bool init();
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_UIOPTION_H__