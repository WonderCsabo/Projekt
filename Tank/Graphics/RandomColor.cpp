#include "RandomColor.h"


RandomColor::RandomColor(void)
{
}

sf::Color RandomColor::getRandomColor()
{
	switch(std::rand()%10)
	{
	case 0:
		return sf::Color(18,148,12);
	case 1:
		return sf::Color(83,223,76);
	case 2:
		return sf::Color(134,249,128);
	case 3:
		return sf::Color(116,178,82);
	case 4:
		return sf::Color(49,108,17);
	case 5:
		return sf::Color(45,90,20);
	case 6:
		return sf::Color(167,140,12);
	case 7:
		return sf::Color(222,198,85);
	case 8:
		return sf::Color(179,106,34);
	case 9:
		return sf::Color(22,209,79);
	default:
		return sf::Color(0,255,78);
	}
	return sf::Color(0,255,0);
}

RandomColor::~RandomColor(void)
{
}
