#include "RandomColor.h"


RandomColor::RandomColor(void)
{
}
RandomColor::~RandomColor(void)
{
}
sf::Color RandomColor::getRandomColor()
{
    switch(std::rand()%6)
    {
    case 0:
        return sf::Color(0,255,0);
    case 1:
        return sf::Color(255,255,255);
    case 2:
        return sf::Color(134,249,128);
    case 3:
        return sf::Color(218,148,18);
    case 4:
        return sf::Color(44,73,192);
    default:
        return sf::Color(202,34,38);
    }
    return sf::Color(202,34,38);
}
