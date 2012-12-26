#pragma once
#ifndef COORD_HPP
#define COORD_HPP

struct Coord
{
	Coord(unsigned int x_, unsigned int y_) : x(x_), y(y_) {};
	Coord(const Coord& c)
	{
		x = c.x;
		y = c.y;
	}

	std::string toString()
	{
		return x + ";" + y;
	}

	unsigned int x;
	unsigned int y;
};

#endif //COORD_HPP