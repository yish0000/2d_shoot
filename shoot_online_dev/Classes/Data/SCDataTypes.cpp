/*
 * ------------------------------------------------------------------------
 *  Name:   SCDataTypes.cpp
 *  Desc:   ����ģ������
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