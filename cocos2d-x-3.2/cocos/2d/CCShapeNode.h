/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CCSHAPENODE_H_
#define __CCSHAPENODE_H_

#include "CCDrawingPrimitives.h"
#include "CCNode.h"

NS_CC_BEGIN

class ShapeNode : public Node
{
public:
    const Color4F& getLineColor(void) {
        return m_color;
    }

    void setLineColor(const Color4F& color) {
        m_color = color;
    }

    float getLineWidth(void) {
        return m_lineWidth;
    }

    void setLineWidth(float lineWidth) {
        m_lineWidth = lineWidth;
    }

    GLushort getLineStipple(void) {
        return m_lineStipple;
    }

    void setLineStipple(GLushort pattern) {
        m_lineStipple = pattern;
    }

    bool isLineStippleEnabled(void) {
        return m_lineStippleEnabled;
    }

    void setLineStippleEnabled(bool lineStippleEnabled) {
        m_lineStippleEnabled = lineStippleEnabled;
    }

    void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);

protected:
    ShapeNode(void)
		: m_lineWidth(1.0f)
		, m_lineStipple(0xFFFF)
		, m_lineStippleEnabled(false)
    {
        m_color = Color4F(0, 0, 0, 1);
    }

    Color4F m_color;
    float     m_lineWidth;
    GLushort  m_lineStipple;
    bool      m_lineStippleEnabled;

    virtual void beforeDraw(void);
    virtual void drawProc(void) = 0;
    virtual void afterDraw(void);

    inline const Point getDrawPosition(void) {
        const Size& size = getContentSize();
        return Point(size.width / 2, size.height / 2);
    }
};

class CircleShape : public ShapeNode
{
public:
    static CircleShape* create(float radius);
	static CircleShape* create(float radius, bool fill);

    float getRadius(void) {
        return m_radius;
    }

    void setRadius(float radius) {
        m_radius = radius;
    }

    float getAngle(void) {
        return m_angle;
    }

    void setAngle(float angle) {
        m_angle = angle;
    }

    unsigned int getSegments(void) {
        return m_segments;
    }

    void setSegments(unsigned int segments) {
        m_segments = segments;
    }

    bool isDrawLineToCenter(void) {
        return m_drawLineToCenter;
    }

    void setDrawLineToCenter(bool drawLineToCenter) {
        m_drawLineToCenter = drawLineToCenter;
    }

    float getScaleX(void) {
        return m_scaleX;
    }

    void setScaleX(float xScale) {
        m_scaleX = xScale;
    }

    float getScaleY(void) {
        return m_scaleY;
    }

    void setScaleY(float yScale) {
        m_scaleY = yScale;
    }

	bool isFill(void) {
		return m_fill;
	}

	void setFill(bool fill) {
		m_fill = fill;
	}
protected:
    CircleShape(float radius)
		: m_radius(radius)
		, m_angle(0)
		, m_segments(32)
		, m_drawLineToCenter(false)
		, m_scaleX(1.0f)
		, m_scaleY(1.0f)
		, m_fill(false)
    {
    }

    float m_radius;
    float m_angle;
    unsigned int m_segments;
    bool m_drawLineToCenter;
    float m_scaleX;
    float m_scaleY;
	bool m_fill;

    virtual void drawProc(void);
};

class RectShape : public ShapeNode
{
public:
    static RectShape* create(const Size& size);

    const Size& getSize(void) {
        return m_size;
    }

    void setSize(const Size& size) {
        m_size = size;
    }

    bool isFill(void) {
        return m_fill;
    }

    void setFill(bool fill) {
        m_fill = fill;
    }

protected:
    RectShape(const Size& size)
		: m_size(size)
		, m_fill(false)
    {
    }

    Size m_size;
    bool m_fill;

    virtual void drawProc(void);
};

class PointShape : public ShapeNode
{
public:
    static PointShape* create(void);

protected:
    virtual void drawProc(void);
};

class PolygonShape : public ShapeNode
{
public:
    static PolygonShape* create(Point* vertices, unsigned int numVertices);
    static PolygonShape* create(PointArray* vertices);
    ~PolygonShape(void);

    bool isFill(void) {
        return m_fill;
    }

    void setFill(bool fill) {
        m_fill = fill;
    }

    bool isClose(void) {
        return m_close;
    }

    void setClose(bool close) {
        m_close = close;
    }

protected:
    PolygonShape(void)
		: m_vertices(NULL)
		, m_verticesDraw(NULL)
		, m_numberOfVertices(0)
		, m_fill(false)
		, m_close(false)
    {
    }
    bool initWithVertices(Point* vertices, unsigned int numVertices);
    bool initWithVertices(PointArray* vertices);

    Point* m_vertices;
    Point* m_verticesDraw;
    unsigned int m_numberOfVertices;
    bool m_fill;
    bool m_close;

    virtual void drawProc(void);
};

NS_CC_END

#endif /* __CCSHAPE_H_ */
