/*
* ------------------------------------------------------------------------
*  Name:   SCUICustom.cpp
*  Desc:   ��Ϸ��ʼ����
*  Author: Yish
*  Date:   2015/8/20
* ------------------------------------------------------------------------
*/

#include "SCUICustom.h"

SCUICustom::SCUICustom(const std::string& name, const std::string& filename)
	: SCUIBase(name, filename)
{
}

SCUICustom::~SCUICustom()
{
}

bool SCUICustom::init()
{
	if (!SCUIBase::init())
		return false;

	return true;
}