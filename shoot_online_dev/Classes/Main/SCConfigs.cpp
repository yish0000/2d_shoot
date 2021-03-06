﻿/*
 * ------------------------------------------------------------------------
 *  Name:   SCConfigs.cpp
 *  Desc:   游戏全局配置数据
 *  Author: Yish
 *  Date:   2015/5/28
 * ------------------------------------------------------------------------
 */

#include "SCConfigs.h"
#include "Network/netlib/libjson/json/json.h"
#include "cocos2d.h"

USING_NS_CC;

SCConfigs::SCConfigs()
	: m_bShowBoundingBox(false)
{
}

SCConfigs& SCConfigs::getInstance()
{
	static SCConfigs obj;
	return obj;
}

// 加载配置文件
bool SCConfigs::load(const char* filename)
{
	Json::Value rootNode;
	Json::Reader json;

	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		CCLOG("SCConfigs::load, load the config file failed! (%s)", filename);
		return false;
	}

	std::string content = FileUtils::getInstance()->getStringFromFile(filename);
	if( !json.parse(content, rootNode) )
	{
		CCLOG("SCConfigs::load, parse the file content failed! (%s)", filename);
		return false;
	}

	scnet::JsonStream stream(rootNode);
	stream.popRootObject(*this);
	return true;
}

void SCConfigs::encode(scnet::JsonStream &stream) const
{
	stream.push("show_box", m_bShowBoundingBox);
}

void SCConfigs::decode(const scnet::JsonStream &stream)
{
	stream.pop("show_box", m_bShowBoundingBox);
}