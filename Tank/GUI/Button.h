#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "Label.h"

class Button : public Label
{
public:
	Button(std::string, sf::RenderWindow*, Coord*, std::string, int, int);
	virtual ~Button();
	virtual void draw();
	virtual void onClick(void());

private:
	sf::RectangleShape* rect;
};

#endif //BUTTON_H