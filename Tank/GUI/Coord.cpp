#include "Coord.h"

Coord::Coord(float x_, float y_) : x(x_), y(y_) {}

Coord::Coord(const Coord& c)
{
	x = c.x;
	y = c.y;
}

Coord& Coord::operator=(const Coord& c)
{
	x = c.x;
	y = c.y;
	return *this;
}

std::string Coord::toString() const
{
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

std::ostream& operator<< (std::ostream& o, const Coord& coord) {
	o << coord.x << ";" << coord.y;
	return o;
}
