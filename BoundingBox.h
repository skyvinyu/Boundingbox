#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include "Point2d.h"
#include <ostream>
#include <boost/shared_ptr.hpp>

namespace geo {

class BoundingBox {
public:
	BoundingBox();
	BoundingBox(double minx, double maxx, double miny, double maxy);
	BoundingBox(const Point2d& leftBottomPnt, const Point2d& rightTopPnt);
	BoundingBox(const BoundingBox& box);
	virtual ~BoundingBox();

	const double getMinX()const {return m_minX;}
	const double getMaxX()const {return m_maxX;}
	const double getMinY()const {return m_minY;}
	const double getMaxY()const {return m_maxY;}

	void setMinX(double minx);
	void setMaxX(double maxx);
	void setMinY(double miny);
	void setMaxY(double maxy);

    void leftBottomPoint(Point2d& lb) const {
        lb.setX(m_minX);
        lb.setY(m_minY);
    }
    void leftMidPoint(Point2d& lb) const {
        lb.setX(m_minX);
        lb.setY((m_maxY+m_minY)/2.0);
    }
    void leftTopPoint(Point2d& lb) const {
        lb.setX(m_minX);
        lb.setY(m_maxY);
    }
    void midTopPoint(Point2d& lb) const {
        lb.setX((m_maxX+m_minX)/2.0);
        lb.setY(m_maxY);
    }
    void rightTopPoint(Point2d& lb) const {
        lb.setX(m_maxX);
        lb.setY(m_maxY);
    }
    void rightMidPoint(Point2d& lb) const {
        lb.setX(m_maxX);
        lb.setY((m_maxY+m_minY)/2.0);
    }
    void rightBottomPoint(Point2d& lb) const {
        lb.setX(m_maxX);
        lb.setY(m_minY);
    }
    void midBottomPoint(Point2d& lb) const {
        lb.setX((m_maxX+m_minX)/2.0);
        lb.setY(m_minY);
    }
    
    void corners(Point2d cornerPoints[]) const{
        leftBottomPoint(cornerPoints[0]);
        leftTopPoint(cornerPoints[1]);
        rightTopPoint(cornerPoints[2]);
        rightBottomPoint(cornerPoints[3]);
    }
    
    void controls(Point2d controlPoints[]) const {
        leftBottomPoint(controlPoints[0]);
        leftMidPoint(controlPoints[1]);
        leftTopPoint(controlPoints[2]);
        midTopPoint(controlPoints[3]);
        rightTopPoint(controlPoints[4]);
        rightMidPoint(controlPoints[5]);
        rightBottomPoint(controlPoints[6]);
        midBottomPoint(controlPoints[7]);
    } 

    void setLeftBottomPoint(const Point2d& p) { m_minX = p.getX(); m_minY = p.getY();}
    void setRightTopPoint(const Point2d& p)   { m_maxX = p.getX(); m_maxY = p.getY();}
    
	bool valid() const;

    /**
     * Grossi la bounding box courante pour englober la bounding box @other
     * @retrun true si la bounding box courante est modifiée
     * @param other
     * @return 
     */
	bool add(const BoundingBox& other);
    /**
     * Grossi la bounding box courante pour englober le point @point
     * @retrun true si la bounding box courante est modifiée
     * @param other
     * @return 
     */
	bool addPoint(const Point2d& point);
    /**
     * Grossi la bounding box courante pour englober les points @points
     * @retrun true si la bounding box courante est modifiée
     * @param other
     * @return 
     */
	bool addPoints(const Point2dArray& points);
	bool intersects(const BoundingBox& other) const;
    bool contains(const Point2d& point) const;
    /**
     * Tests whether the BoundingBox overlaps another bounding volume.
     * @param other another bounding volume
     * @return true if contrain the other bbox false if not
     */
    bool contains(const BoundingBox& other) const;
    /**
     * Tests whether the BoundingBox roughly contains a point. 
     *  (Roughly means the disparancy is not larger than 0.2)
     *  This is useful for a contain test of projected bounding box (lat/lon to meter)
     * @param point 
     * @return true if roughly contrain the point false if not
     */
    bool roughContains(const Point2d& point) const;

	double width() const;
	double height() const;
	void center(Point2d& point);
	bool operator==(const BoundingBox& other) const;

	BoundingBox& operator=(const BoundingBox& other);
	BoundingBox& operator+=(const BoundingBox& other);
	BoundingBox& operator*=(double ratio);
	BoundingBox& operator/=(double ratio);
    double operator[](int index) const;
    
    friend std::ostream& operator<<(std::ostream& out, const BoundingBox& bb);

    virtual void load(const boost::property_tree::ptree& tree);
    
private:
	double m_minX;
	double m_maxX;
	double m_minY;
	double m_maxY;
};

typedef boost::shared_ptr<BoundingBox> PBoundingBox;

}

#endif /* BOUNDINGBOX_H_ */
