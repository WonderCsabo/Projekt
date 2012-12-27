#pragma once

#include <sstream>

struct Coord
{
	Coord(float x_, float y_) : x(x_), y(y_) {};
	Coord(const Coord& c)
	{
		x = c.x;
		y = c.y;
	}

	std::string toString()
	{
		std::stringstream ss;
		ss << x << ";" << y;
		std::string ret;
		std::getline(ss, ret);
		return ret;
	}

	float x;
	float y;
};