#include "GuiElement.h"

GuiElement::GuiElement(std::string id_, sf::RenderWindow* rw, Coord* pos, std::string txt) : id(id_), window(rw), position(pos), text(txt)
{
	width = height = 0;
}

GuiElement::~GuiElement()
{
	delete position;
}

std::string GuiElement::getText() const
{
	return text;
}

int GuiElement::getType() const
{
	return TYPE;
}

void GuiElement::setText(std::string t)
{
	text = t;
	draw();
}

Coord* GuiElement::getPosition() const
{
	return position;
}

bool GuiElement::isMouseClicked(sf::Event ev)
{
	if (ev.mouseButton.x>position->x && ev.mouseButton.y>position->y &&
		ev.mouseButton.x<position->x+width && ev.mouseButton.y<position->y+height &&
		ev.type==sf::Event::MouseButtonPressed && ev.mouseButton.button==sf::Mouse::Button::Left)
		return true;
	else
		return false;
}