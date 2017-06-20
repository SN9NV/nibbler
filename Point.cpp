#include "Point.hpp"

Nibbler::Point::Point() {}

Nibbler::Point::Point(unsigned x, unsigned y) :
	x(x), y(y) {}

Nibbler::Point::Point(const Point &src) {
	*this = src;
}

Nibbler::Point& Nibbler::Point::operator=(const Point &rhs) {
	this->x = rhs.x;
	this->y = rhs.y;

	return *this;
}

bool Nibbler::Point::operator==(const Point &p2) const {
	return (this->x == p2.x && this->y == p2.y);
}

Nibbler::Point::~Point() {}