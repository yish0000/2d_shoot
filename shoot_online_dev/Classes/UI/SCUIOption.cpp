/*
 * ------------------------------------------------------------------------
 *  Name:   SCUIOption.cpp
 *  Desc:   ����ѡ�����
 *  Author: Yish
 *  Date:   2015/8/20
 * ------------------------------------------------------------------------
 */

#include "SCUIOption.h"

SCUIOption::SCUIOption(const std::string& name, const std::string& filename)
	: SCUIBase(name, filename)
{
}

SCUIOption::~SCUIOption()
{
}

bool SCUIOption::init()
{
	if (!SCUIBase::init())
		return false;

	return true;
}