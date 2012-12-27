#pragma once

#include <SFML/Graphics.hpp>
#include "Label.h"

class Button : public Label
{
public:
	Button(std::string, sf::RenderWindow*, Coord, std::string, float, float);
	virtual ~Button();
	virtual void draw();
	virtual void onClick(void());

private:
	sf::RectangleShape* rect;
};
