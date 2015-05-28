/*
 * ------------------------------------------------------------------------
 *  Name:   SCConfigs.h
 *  Desc:   APP配置信息
 *  Author: Yish
 *  Date:   2015/5/28
 * ------------------------------------------------------------------------
 */

#ifndef __SC_CONFIGS_H__
#define __SC_CONFIGS_H__

#include <string>
#include "Network/netlib/stream/JsonStream.h"

class SCConfigs : public scnet::JsonStreamObj
{
public:
	~SCConfigs() {}
	
	// 加载配置信息(json文件)
	bool load(const char* filename);

	bool isShowBoundingBox() const { return m_bShowBoundingBox; }

	static SCConfigs& getInstance();

protected:
	bool m_bShowBoundingBox;	// 是否显示包围盒

protected:
	SCConfigs();

	void encode(scnet::JsonStream &stream) const;
	void decode(const scnet::JsonStream &stream);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_CONFIGS_H__