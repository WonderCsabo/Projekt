#pragma once
#include <SFML/Graphics.hpp>
class RandomColor
{
public:
	RandomColor(void);
	~RandomColor(void);
	static sf::Color getRandomColor();
};

