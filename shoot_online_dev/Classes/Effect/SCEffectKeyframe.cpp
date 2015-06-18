/*
 * ------------------------------------------------------------------------
 *  Name:   SCEffectKeyframe.cpp
 *  Desc:   特效关键帧数据
 *  Author: Yish
 *  Date:   2015/6/8
 * ------------------------------------------------------------------------
 */

#include "cocos2d.h"
#include "SCEffectKeyframe.h"

USING_NS_CC;
using namespace tinyxml2;

// 每帧跨越的时间
static const float FRAME_SPAN_TIME = 1.0f / 30.0f;

template <typename T>
inline T Lerpf(const T& v1, const T& v2, float s)
{
	return v1 + ( v2 - v1) * s;
}

template <class T>
struct SCKeyValue
{
	float m_frame;
	T m_value;

	SCKeyValue() : m_frame(0.0f) {}
	SCKeyValue(float frame, const T& value) : m_frame(frame), m_value(value) {}
};

template <class T>
class SCControlDataBase
{
	typedef std::vector<SCKeyValue<T> > KeyValueList;

public:
	SCControlDataBase() {}
	virtual ~SCControlDataBase() {}

	virtual ActionInterval* getAction() const
	{
		if( m_data.empty() )
			return NULL;

		float fLastTime = 0.0f;
		Vector<FiniteTimeAction*> actions;
		for(typename KeyValueList::const_iterator it=m_data.begin(); it!=m_data.end(); ++it)
		{
			const SCKeyValue<T>& data = *it;
			float fCurTime = data.m_frame * FRAME_SPAN_TIME;
			ActionInterval* pAction = getAction(fCurTime - fLastTime, data.m_value);
			fLastTime = fCurTime;
			actions.pushBack(pAction);
		}

		return Sequence::create(actions);
	}

protected:
	virtual ActionInterval* getAction(float fTime, const T& data) const = 0;

protected:
	KeyValueList m_data;
};

/** 半透明的控制
*/
class SCAlphaControl : public SCControlDataBase<GLubyte>, public SCEffectKeyframeControl
{
public:
	SCAlphaControl() : SCEffectKeyframeControl(EFT_KEYFRAME_ALPHA) {}
	~SCAlphaControl() {}

	bool loadData(tinyxml2::XMLElement* xmlNode, int startFrame)
	{
		XMLElement* pChild = xmlNode->FirstChildElement();
		while(pChild)
		{
			float frame = pChild->FloatAttribute("frame");
			GLubyte alpha = (GLubyte)pChild->IntAttribute("alpha");
			if( startFrame > 0 ) frame += startFrame;
			m_data.push_back(SCKeyValue<GLubyte>(frame, alpha));
			pChild = pChild->NextSiblingElement();
		}

		return true;
	}

	ActionInterval* getAction() const
	{
		return SCControlDataBase::getAction();
	}

protected:
	ActionInterval* getAction(float fTime, const GLubyte& data) const
	{
		return FadeTo::create(fTime, data);
	}
};

/** 缩放控制
*/
class SCScaleControl : public SCControlDataBase<Point>, public SCEffectKeyframeControl
{
public:
	SCScaleControl() : SCEffectKeyframeControl(EFT_KEYFRAME_SCALE) {}
	~SCScaleControl() {}

	bool loadData(tinyxml2::XMLElement* xmlNode, int startFrame)
	{
		XMLElement* pChild = xmlNode->FirstChildElement();
		while(pChild)
		{
			float frame = pChild->FloatAttribute("frame");
			float x = pChild->FloatAttribute("x");
			float y = pChild->FloatAttribute("y");
			if( startFrame > 0 ) frame += startFrame;
			m_data.push_back(SCKeyValue<Point>(frame, Point(x, y)));
			pChild = pChild->NextSiblingElement();
		}

		return true;
	}

	ActionInterval* getAction() const
	{
		return SCControlDataBase::getAction();
	}

protected:
	ActionInterval* getAction(float fTime, const Point& data) const
	{
		return ScaleTo::create(fTime, data.x, data.y);
	}
};

/** 旋转控制
*/
class SCRotationControl : public SCControlDataBase<float>, public SCEffectKeyframeControl
{
	class SCRotateTo : public RotateTo
	{
	public:
		static SCRotateTo* create(float fDuration, float fDeltaAngle)
		{
			SCRotateTo* pRotateTo = new SCRotateTo();
			pRotateTo->initWithDuration(fDuration, fDeltaAngle);
			pRotateTo->autorelease();
			return pRotateTo;
		}

		virtual void startWithTarget(Node *pTarget)
		{
			ActionInterval::startWithTarget(pTarget);
			
			_startAngleX = pTarget->getRotationSkewX();
			_startAngleY = _target->getRotationSkewY();
			_diffAngleX = _dstAngleX - _startAngleX;
			_diffAngleY = _dstAngleY - _startAngleY;
		}
	};

public:
	SCRotationControl() : SCEffectKeyframeControl(EFT_KEYFRAME_ROTATION) {}
	~SCRotationControl() {}

	bool loadData(tinyxml2::XMLElement* xmlNode, int startFrame)
	{
		XMLElement* pChild = xmlNode->FirstChildElement();
		while(pChild)
		{
			float frame = pChild->FloatAttribute("frame");
			float rot = -pChild->FloatAttribute("rot");
			if( startFrame > 0 ) frame += startFrame;
			m_data.push_back(SCKeyValue<float>(frame, rot));
			pChild = pChild->NextSiblingElement();
		}

		return true;
	}

	ActionInterval* getAction() const
	{
		return SCControlDataBase::getAction();
	}

protected:
	ActionInterval* getAction(float fTime, const float& data) const
	{
		return SCRotateTo::create(fTime, data);
	}
};

/** 颜色控制
*/
class SCColorControl : public SCControlDataBase<Color3B>, public SCEffectKeyframeControl
{
public:
	SCColorControl() : SCEffectKeyframeControl(EFT_KEYFRAME_COLOR) {}
	~SCColorControl() {}

	bool loadData(tinyxml2::XMLElement* xmlNode, int startFrame)
	{
		XMLElement* pChild = xmlNode->FirstChildElement();
		while(pChild)
		{
			float frame = pChild->FloatAttribute("frame");
			GLubyte r = (GLubyte)pChild->IntAttribute("r");
			GLubyte g = (GLubyte)pChild->IntAttribute("g");
			GLubyte b = (GLubyte)pChild->IntAttribute("b");
			if( startFrame > 0 ) frame += startFrame;
			m_data.push_back(SCKeyValue<Color3B>(frame, Color3B(r, g, b)));
			pChild = pChild->NextSiblingElement();
		}

		return true;
	}

	ActionInterval* getAction() const
	{
		return SCControlDataBase::getAction();
	}

protected:
	ActionInterval* getAction(float fTime, const Color3B& data) const
	{
		return TintTo::create(fTime, data.r, data.g, data.b);
	}
};

/** 移动控制
*/
class SCPositionControl : public SCControlDataBase<Point>, public SCEffectKeyframeControl
{
public:
	SCPositionControl() : SCEffectKeyframeControl(EFT_KEYFRAME_POSITION) {}
	~SCPositionControl() {}

	bool loadData(tinyxml2::XMLElement* xmlNode, int startFrame)
	{
		XMLElement* pChild = xmlNode->FirstChildElement();
		while(pChild)
		{
			float frame = pChild->FloatAttribute("frame");
			float x = pChild->FloatAttribute("x");
			float y = -pChild->FloatAttribute("y");
			if( startFrame > 0 ) frame += startFrame;
			m_data.push_back(SCKeyValue<Point>(frame, Point(x, y)));
			pChild = pChild->NextSiblingElement();
		}

		return true;
	}

	ActionInterval* getAction() const
	{
		return SCControlDataBase::getAction();
	}

protected:
	ActionInterval* getAction(float fTime, const Point& data) const
	{
		return MoveTo::create(fTime, data);
	}
};

///////////////////////////////////////////////////////////////////////////
// class SCEffectKeyframe

SCEffectKeyframeData::SCEffectKeyframeData()
{
}

SCEffectKeyframeData::~SCEffectKeyframeData()
{
	clear();
}

void SCEffectKeyframeData::clear()
{
	KeyframeControlList::iterator it = m_keyframes.begin();
	for(; it!=m_keyframes.end(); ++it)
	{
		delete (*it);
	}

	m_keyframes.clear();
}

bool SCEffectKeyframeData::loadKeyframeData(tinyxml2::XMLElement* xmlNode, int startFrame)
{
	clear();

	int start_frame = xmlNode->IntAttribute("start_frame");
	int end_frame = xmlNode->IntAttribute("end_frame");
	int layer = xmlNode->IntAttribute("layer");

	SCEffectKeyframeControl* pControl = NULL;
	XMLElement* pChild = xmlNode->FirstChildElement();
	while(pChild)
	{
		std::string keyName = pChild->Name();

		if( keyName == "pos" )
			pControl = new SCPositionControl();
		else if( keyName == "alpha" )
			pControl = new SCAlphaControl();
		else if( keyName == "color" )
			pControl = new SCColorControl();
		else if( keyName == "rotation" )
			pControl = new SCRotationControl();
		else if( keyName == "scale" )
			pControl = new SCScaleControl();
		else
		{
			pControl = NULL;
			CCLOG("SCEffectKeyframeData::loadKeyframeData, invalid keyframe type (%s)", keyName.c_str());
		}

		if( pControl )
		{
			pControl->loadData(pChild, startFrame);
			m_keyframes.push_back(pControl);
		}

		pChild = pChild->NextSiblingElement();
	}

	return true;
}

void SCEffectKeyframeData::runKeyframeAction(SCEffectElement* pElement)
{
	KeyframeControlList::iterator it=m_keyframes.begin();
	for(; it!=m_keyframes.end(); ++it)
	{
		SCEffectKeyframeControl* pControl = *it;
		Action* pAction = pControl->getAction();
		if( pAction )
			pElement->runKeyFrameAction(pAction, pControl->getType());
	}
}