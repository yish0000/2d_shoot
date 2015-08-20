/*
* ------------------------------------------------------------------------
*  Name:   SCUIStage.cpp
*  Desc:   游戏开始界面
*  Author: Yish
*  Date:   2015/8/20
* ------------------------------------------------------------------------
*/

#include "SCUIStage.h"

SCUIStage::SCUIStage(const std::string& name, const std::string& filename)
: SCUIBase(name, filename)
{
}

SCUIStage::~SCUIStage()
{
}

bool SCUIStage::init()
{
	if (!SCUIBase::init())
		return false;

	return true;
}