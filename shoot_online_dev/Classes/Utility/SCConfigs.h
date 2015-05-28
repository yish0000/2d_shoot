/*
 * ------------------------------------------------------------------------
 *  Name:   SCConfigs.h
 *  Desc:   APP������Ϣ
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
	
	// ����������Ϣ(json�ļ�)
	bool load(const char* filename);

	bool isShowBoundingBox() const { return m_bShowBoundingBox; }

	static SCConfigs& getInstance();

protected:
	bool m_bShowBoundingBox;	// �Ƿ���ʾ��Χ��

protected:
	SCConfigs();

	void encode(scnet::JsonStream &stream) const;
	void decode(const scnet::JsonStream &stream);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_CONFIGS_H__