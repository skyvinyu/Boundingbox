
#include "BoundingBox.h"

#include <limits>
#include <cmath>

namespace geo {

BoundingBox::BoundingBox()
	:m_minX(std::numeric_limits<double>::infinity()),
	m_maxX(-std::numeric_limits<double>::infinity()),
	m_minY(std::numeric_limits<double>::infinity()),
	m_maxY(-std::numeric_limits<double>::infinity()){}

BoundingBox::BoundingBox(double minx, double maxx, double miny, double maxy)
	:m_minX(minx),
	m_maxX(maxx),
	m_minY(miny),
	m_maxY(maxy){}

BoundingBox::BoundingBox(const Point2d& leftBottomPnt, const Point2d& rightTopPnt)
	:m_minX(leftBottomPnt.getX()),
	m_maxX(rightTopPnt.getX()),
	m_minY(leftBottomPnt.getY()),
	m_maxY(rightTopPnt.getY()){}

BoundingBox::BoundingBox(const BoundingBox& box)
	:m_minX(box.getMinX()),
    m_maxX(box.getMaxX()),
    m_minY(box.getMinY()),
    m_maxY(box.getMaxY()){}

BoundingBox::~BoundingBox() {
}


bool BoundingBox::valid() const
{
    return (m_minX <= m_maxX && m_minY <= m_maxY);
}

void BoundingBox::setMinX(double minx){
	m_minX = minx;
}
void BoundingBox::setMaxX(double maxx){
	m_maxX = maxx;
}
void BoundingBox::setMinY(double miny){
	m_minY = miny;
}
void BoundingBox::setMaxY(double maxy){
	m_maxY = maxy;
}

bool BoundingBox::add(const BoundingBox& other){
    Point2d lb, rt;
    other.leftBottomPoint(lb);
    other.rightTopPoint(rt);
    if( contains(lb) && contains(rt) ) {
        return false;
    }
    addPoint(lb);
    addPoint(rt);
    return true;
}

bool BoundingBox::addPoint(const Point2d& point){
    bool result = false;
    if( point.getX()<m_minX ) {
        setMinX(point.getX());
        result = true;
    }
    if( point.getX()>m_maxX ) {
        setMaxX(point.getX());
        result = true;
    }
    if( point.getY()<m_minY ) {
        setMinY(point.getY());
        result = true;
    }
    if( point.getY()>m_maxY ) {
        setMaxY(point.getY());
        result = true;
    }
    return result;
}

bool BoundingBox::addPoints(const Point2dArray& points){
    bool ret = false;
    for( Point2dArray::const_iterator ite = points.begin(); ite != points.end(); ++ite) {
        ret = addPoint(*ite) | ret;
    }
    return ret;
}

bool BoundingBox::intersects(const BoundingBox& other) const{
    return !(other.getMinX()>m_maxX 
            || other.getMaxX()<m_minX 
            || other.getMinX()>m_maxY 
            || other.getMaxY()<m_minY);
}

bool BoundingBox::contains(const Point2d& point) const {
    return !(point.getX()>m_maxX || point.getX()<m_minX || point.getY()>m_maxY || point.getY()<m_minY);
}

/**
 * Tests whether the BoundingBox roughly contains a point. 
 *  (Roughly means the disparancy is not larger than 0.01)
 *  This is useful contain test after a projection (lat/lon to meter)
 * @param point 
 * @return true if roughly contrain the point false if not
 */
bool BoundingBox::roughContains(const Point2d& point) const {
    double rough = 0.01;
    return !(point.getX()>m_maxX+rough || point.getX()<m_minX-rough || point.getY()>m_maxY+rough || point.getY()<m_minY-rough);
}

bool BoundingBox::contains(const BoundingBox& other) const{
    return (other.getMinX() >= m_minX &&
            other.getMaxX() <= m_maxX &&
            other.getMinY() >= m_minY &&
            other.getMaxY() <= m_maxY);
}

double BoundingBox::width() const{
	return m_maxX-m_minX;
}
double BoundingBox::height() const{
    return m_maxY-m_minY;
}
void BoundingBox::center(Point2d& point){
    point.setX(0.5*(m_minX+m_maxX));
    point.setY(0.5*(m_minY+m_maxY));
}

bool BoundingBox::operator==(const BoundingBox& other) const{
	return m_minX==other.m_minX &&
			m_maxX==other.m_maxX &&
			m_minY==other.m_minY &&
			m_maxY==other.m_maxY;
}

BoundingBox& BoundingBox::operator=(const BoundingBox& other){
    m_minX = other.m_minX;
    m_maxX = other.m_maxX;
    m_minY = other.m_minY;
    m_maxY = other.m_maxY;
	return *this;
}

BoundingBox& BoundingBox::operator*=(double ratio)
{
    Point2d ctr;
    center(ctr);
    double sx = 0.5 * width() * ratio;
    double sy = 0.5 * height() * ratio;
    m_minX = ctr.getX() - sx;
    m_maxX = ctr.getX() + sx;
    m_minY = ctr.getY() - sy;
    m_maxY = ctr.getY() + sy;
    return *this;
}

BoundingBox& BoundingBox::operator/=(double ratio)
{
    Point2d ctr;
    center(ctr);
    double sx = 0.5 * width() / ratio;
    double sy = 0.5 * height() / ratio;
    m_minX = ctr.getX() - sx;
    m_maxX = ctr.getX() + sx;
    m_minY = ctr.getY() - sy;
    m_maxY = ctr.getY() + sy;
    return *this;
}

double BoundingBox::operator[] (int index) const
{
    switch(index) {
    case 0:
        return m_minX;
    case 1:
        return m_minY;
    case 2:
        return m_maxX;
    case 3:
        return m_maxY;
    default:
		throw std::invalid_argument( "index out of range, index 0: MinX, index 1: MinY, index 2: MaxX, index3:MaxY" );
    }
}

std::ostream& operator<<(std::ostream& out, const BoundingBox& bb){
    out << "m_minX = " << bb.getMinX()
        << "; m_maxX = " << bb.getMaxX()
        << "; m_minY = " << bb.getMinY()
        << "; m_maxY = " << bb.getMaxY();
    return out;
}

}
