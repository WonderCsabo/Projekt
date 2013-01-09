#pragma once

#include <sstream>
#include <iostream>

struct Coord
{
    Coord(float x_, float y_);
    Coord(const Coord& c);

    Coord& operator=(const Coord& c);

    std::string toString() const;

    float x;
    float y;
};

std::ostream& operator<< (std::ostream& o, const Coord& coord);

