#include "Point2d.h"

#include <limits>

namespace geo {
    
Point2d::Point2d()
	: m_x(-std::numeric_limits<double>::infinity()),
	  m_y(-std::numeric_limits<double>::infinity()){}

Point2d::Point2d(double x, double y)
	: m_x(x),
	  m_y(y){}

Point2d::Point2d(const Point2d& p)
	: m_x(p.getX()),
	  m_y(p.getY()){}

Point2d::~Point2d() {}

}
