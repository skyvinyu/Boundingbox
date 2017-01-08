#ifndef POINT2D_H_
#define POINT2D_H_

#include <vector>

namespace geo {

class Point2d {
public:
	Point2d();
	Point2d(double x, double y);
	Point2d(const Point2d& p);
	virtual ~Point2d();

	inline const double& getX() const {return m_x;}
	inline const double& getY() const {return m_y;}
 	inline double& getX() {return m_x;}
	inline double& getY() {return m_y;}
    inline void setX(double x) {m_x = x;}
    inline void setY(double y) {m_y = y;}
    
private:
	double m_x;
	double m_y;
};

typedef std::vector<Point2d> Point2dArray;

}

#endif /* POINT2D_H_ */
