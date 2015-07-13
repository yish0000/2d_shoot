/*
 * ------------------------------------------------------------------------
 *  Name:   SCDataTypes.cpp
 *  Desc:   数据模板类型
 *  Author: Yish
 *  Date:   2015/7/7
 * ------------------------------------------------------------------------
 */

#include "SCDataTypes.h"
#include "SCDataModule.h"

void DATA_TEMPL_BASE::release()
{
	g_pDataModule->releaseTemplate(this);
}