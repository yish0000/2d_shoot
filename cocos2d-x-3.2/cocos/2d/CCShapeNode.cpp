#include "CCShapeNode.h"
#include "CCActionCatmullRom.h"

NS_CC_BEGIN

void ShapeNode::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    beforeDraw();
    drawProc();
    afterDraw();
}

void ShapeNode::beforeDraw(void)
{
    glLineWidth(m_lineWidth);
    DrawPrimitives::setDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
#ifdef GL_LINE_STIPPLE
    if (m_lineStippleEnabled)
    {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, m_lineStipple);
    }
#endif
}

void ShapeNode::afterDraw(void)
{
    glLineWidth(1);
    DrawPrimitives::setDrawColor4F(1, 1, 1, 1);
#ifdef GL_LINE_STIPPLE
    if (m_lineStippleEnabled)
    {
        glDisable(GL_LINE_STIPPLE);
        glLineStipple(1, 0xFFFF);
    }
#endif
}

CircleShape* CircleShape::create(float radius)
{
    CircleShape* circle = new CircleShape(radius);
    circle->autorelease();
    return circle;
}

CircleShape* CircleShape::create(float radius, bool fill)
{
	CircleShape* circle = CircleShape::create(radius);
	circle->setFill(fill);
	return circle;
}

void CircleShape::drawProc(void)
{
	if( m_fill )
		DrawPrimitives::drawSolidCircle(getDrawPosition(), m_radius, m_angle, m_segments, m_scaleX, m_scaleY);
	else
	    DrawPrimitives::drawCircle(getDrawPosition(), m_radius, m_angle, m_segments, m_drawLineToCenter, m_scaleX, m_scaleY);
}


RectShape* RectShape::create(const cocos2d::Size &size)
{
    RectShape* rect = new RectShape(size);
    rect->autorelease();
    return rect;
}

void RectShape::drawProc(void)
{
    const Point center = getDrawPosition();
    float w = m_size.width / 2;
    float h = m_size.height / 2;
    
    if (m_fill)
    {
		DrawPrimitives::drawSolidRect(Vec2(center.x - w, center.y + h), Vec2(center.x + w, center.y - h), m_color);
    }
    else
    {
        DrawPrimitives::setDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
        DrawPrimitives::drawRect(Vec2(center.x - w, center.y + h), Vec2(center.x + w, center.y - h));
    }
}


PointShape* PointShape::create(void)
{
    PointShape* point = new PointShape();
    point->autorelease();
    return point;
}

void PointShape::drawProc(void)
{
    DrawPrimitives::drawPoint(getDrawPosition());
}


PolygonShape* PolygonShape::create(Point* vertices, unsigned int numVertices)
{
    PolygonShape* polygon = new PolygonShape();
    polygon->initWithVertices(vertices, numVertices);
    polygon->autorelease();
    return polygon;
}

PolygonShape* PolygonShape::create(PointArray* vertices)
{
    PolygonShape* polygon = new PolygonShape();
    polygon->initWithVertices(vertices);
    polygon->autorelease();
    return polygon;
}

bool PolygonShape::initWithVertices(Point* vertices, unsigned int numVertices)
{
    m_numberOfVertices = numVertices;
    m_vertices = new Point[m_numberOfVertices];
    m_verticesDraw = new Point[m_numberOfVertices];
    for (unsigned int i = 0; i < m_numberOfVertices; ++i)
    {
        m_verticesDraw[i] = m_vertices[i] = vertices[i];
    }
    return true;
}

bool PolygonShape::initWithVertices(PointArray* vertices)
{
	Point *points = new Point[vertices->count()];
	const std::vector<Point*>* pVecVerts = vertices->getControlPoints();
	std::vector<Point*>::const_iterator iter;
	int index = 0;
	for (iter = pVecVerts->cbegin(); iter != pVecVerts->cend(); ++iter)
	{
		points[index++] = *(*iter);
	}
    bool ret = initWithVertices(points, vertices->count());
    delete []points;
    return ret;
}

PolygonShape::~PolygonShape(void)
{
    delete[] m_vertices;
    delete[] m_verticesDraw;
}

void PolygonShape::drawProc(void)
{
    const Point center = getDrawPosition();
    for (unsigned int i = 0; i < m_numberOfVertices; ++i)
    {
        m_verticesDraw[i].x = m_vertices[i].x + center.x;
        m_verticesDraw[i].y = m_vertices[i].y + center.y;
    }
    
    if (m_fill)
    {
        DrawPrimitives::drawSolidPoly(m_verticesDraw, m_numberOfVertices, m_color);
    }
    else
    {
        DrawPrimitives::setDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
        DrawPrimitives::drawPoly(m_verticesDraw, m_numberOfVertices, m_close);
    }
}

NS_CC_END
