#include <math.h>
#ifndef _CIRCLE_H
#define _CIRCLE_H

const double pi = 3.1416;

class Point {
public:
	Point() : _x(0), _y(0) {};
	Point(int x, int y) : _x(x), _y(y) {};

	int getX() const;
	int getY() const;

	void setValues(const int x, const int y);

private:
	int _x;
	int _y;
};

int Point::getX() const {
	return _x;
}

int Point::getY() const {
	return _y;
}

void Point::setValues(const int x, const int y) {
	_x = x;
	_y = y;
}




class Circle {
public:
	Circle() : _left(Point()), _right(Point()) {};
	Circle(Point &l, Point &r) : _left(l), _right(r) { _radius = (_right.getX() - _left.getX()) / 2; };

	void setValues(const Point l, const Point r);

	int area() const;
	bool isInside(const Point &point) const;

private:
	Point _left;
	Point _right;
	double _radius;
};

void Circle::setValues(const Point l, const Point r) {
	_left = l;
	_right = r;
	_radius = (_right.getX() - _left.getX()) / 2;
}

int Circle::area() const {
	return pi * pow(_radius, 2);
}

bool Circle::isInside(const Point &point) const {
	double centerX, centerY;
	bool inside;
	
	centerX = _right.getX() - _radius;
	centerY = _right.getY();

	if(sqrt(pow((point.getX() - centerX), 2) + pow((point.getY() - centerY), 2)) > _radius)
		inside = false;
	else
		inside = true;

	return inside;
}

#endif