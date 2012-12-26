#include "Button.h"

Button::Button(std::string id_, sf::RenderWindow* rw, Coord* pos, std::string txt, float w, float h) : Label(id_, rw, pos, txt)
{
	TYPE = GuiElement::BTN;
	width = w;
	height = h;
	rect = new sf::RectangleShape;//(position->x, position->y, width, height);
	sf::Vector2f v(width,height);
	rect->setSize(v);
	rect->setFillColor(sf::Color(100,100,100));
	rect->setPosition(position->x, position->y);
	draw();
}

Button::~Button()
{
	delete position;
	delete rect;
}

void Button::onClick(void (*func)())
{
	(*func)();
}

void Button::draw()
{
	sf::Text t(text);
	t.setPosition(position->x+5.0f, position->y+5.0f);
	t.setCharacterSize(12);
	//width = t.getGlobalBounds().width;
	//height = t.getGlobalBounds().height;
	window->draw(*rect);
	window->draw(t);
	//window->display();
}