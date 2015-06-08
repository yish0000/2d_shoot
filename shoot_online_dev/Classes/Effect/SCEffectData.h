/*
 * ------------------------------------------------------------------------
 *  Name:   SCEffectData.h
 *  Desc:   特效数据
 *  Author: Yish
 *  Date:   2015/6/8
 * ------------------------------------------------------------------------
 */

#ifndef __SC_EFFECTDATA_H__
#define __SC_EFFECTDATA_H__

#include "base/CCRef.h"
#include "SCEffectKeyframe.h"

enum
{
	EFT_PLAYMODE_LOOP,
	EFT_PLAYMODE_LOOPNUM,
	EFT_PLAYMODE_TIME,
};

/** 特效元素数据
*/
class SCEffectElementData : public cocos2d::Ref
{
public:
	SCEffectElementData(int type) : m_iType(type), m_iLayer(0), m_iLoopCount(-1) {}
	virtual ~SCEffectElementData() {}

	virtual bool loadData(tinyxml2::XMLElement* pNode) = 0;

	int getLoopCount() const { return m_iLoopCount; }
	void setLoopCount(int count) { m_iLoopCount = count; }
	int getLayer() const { return m_iLayer; }
	const std::string& getFilename() const { return m_sFilename; }
	const SCEffectKeyframeData& getKeyframe() const { return m_keyframe; }
	int getType() const { return m_iType; }

protected:
	int m_iType;
	std::string m_sFilename;
	int m_iLoopCount;
	int m_iLayer;
	SCEffectKeyframeData m_keyframe;
};

/** 特效数据
*/
class SCEffectData : public cocos2d::Ref
{
public:

	typedef std::vector<SCEffectElementData*> ElementDataList;

public:
	SCEffectData();
	virtual ~SCEffectData();

	bool loadEffectData(const char* filename);
	int getFrameCount() const { return m_iFrameCount; }
	int getShakeEventFrame() const { return m_iShakeEventFrame; }
	int getShakeEventData() const { return m_iShakeEventData; }
	int getDivide() const { return m_iFrontBackDivide; }
	int getLoopCount() const { return m_iLoopCount; }
	const ElementDataList& getElementList() const { return m_elements; }

protected:
	int m_iLoopCount;
	int m_iFrontBackDivide;
	int m_iFrameCount;
	int m_iShakeEventFrame;
	int m_iShakeEventData;
	ElementDataList m_elements;
};

/** 特效数据缓存
*/
class SCEffectDataCache
{
	typedef std::map<std::string, SCEffectData*> EffectDataMap;

public:
	SCEffectDataCache() {}
	~SCEffectDataCache() {}

	static SCEffectDataCache& getInstance();
	SCEffectData* getEffectData(const char* filename);

protected:
	EffectDataMap m_effects;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_EFFECTDATA_H__