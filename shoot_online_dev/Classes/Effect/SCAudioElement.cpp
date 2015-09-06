/*
 * ------------------------------------------------------------------------
 *  Name:   SCAudioElement.cpp
 *  Desc:   ÉùÒôÔªËØ
 *  Author: Yish
 *  Date:   2015/6/18
 * ------------------------------------------------------------------------
 */

#include "SCEffectData.h"
#include "SCAudioElement.h"

class SCAudioElementData : public SCEffectElementData
{
public:
	SCAudioElementData()
		: SCEffectElementData(EFT_ELEMENT_AUDIO), m_iPlayMode(EFT_PLAYMODE_TIME)
		, m_fPlayTime(0.0f), m_iStartFrame(0), m_iEndFrame(0)
	{
	}

	bool loadData(tinyxml2::XMLElement* pNode)
	{
		m_iStartFrame = pNode->IntAttribute("start_frame");
		m_iEndFrame = pNode->IntAttribute("end_frame");
		m_iLayer = pNode->IntAttribute("layer");
		if( m_iLayer < 0 ) m_iLayer = 0;
		int systemLevel = pNode->IntAttribute("level");
		if( pNode->Attribute("file") )
			m_sFilename = pNode->Attribute("file");
		m_iLoopCount = pNode->IntAttribute("loop");
		return true;
	}

	int getPlayMode() const { return m_iPlayMode; }
	float getPlayTime() const { return m_fPlayTime; }
	int getStartFrame() const { return m_iStartFrame; }
	int getEndFrame() const { return m_iEndFrame; }

protected:
	int m_iPlayMode;
	float m_fPlayTime;
	int m_iStartFrame;
	int m_iEndFrame;
};

//////////////////////////////////////////////////////////////////////////////

SCAudioElement::SCAudioElement() : SCEffectElement(EFT_ELEMENT_AUDIO), m_pData(NULL)
{
}

SCAudioElement::~SCAudioElement()
{
}

bool SCAudioElement::init(SCEffectElementData *pData, bool stepAction)
{
    if( !pData || pData->getType() != EFT_ELEMENT_AUDIO )
        return false;
    
    m_pData = dynamic_cast<SCAudioElementData*>(pData);
    if( !m_pData ) return false;

    return true;
}

