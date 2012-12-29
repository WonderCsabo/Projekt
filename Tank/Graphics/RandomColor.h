#pragma once
#include <SFML/Graphics.hpp>
class RandomColor
{
public:
	RandomColor(void);
	static sf::Color getRandomColor();
	~RandomColor(void);
};

