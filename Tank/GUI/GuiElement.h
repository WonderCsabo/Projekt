#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Coord.h"

class GuiElement
{
public:
	GuiElement(std::string, sf::RenderWindow*, Coord*, std::string);
	virtual ~GuiElement();
	std::string getText() const;
	Coord* getPosition() const;
	virtual void setText(std::string);
	bool isMouseClicked(sf::Event);
	virtual void draw() = 0;
	int getType() const;
	std::string id;

	enum TYPES
	{
	BTN = 101, //button
	LBL = 100, //label
	EDT = 102  //editbox
	};

protected:
	Coord* position;
	int TYPE;
	float width;
	float height;
	std::string text;
	sf::RenderWindow* window;
};