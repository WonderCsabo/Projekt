#include "Label.h"

Label::Label(std::string id_, sf::RenderWindow* rw, Coord* pos, std::string txt) : GuiElement(id_, rw, pos, txt)
{
	TYPE = GuiElement::LBL;
	draw();
}

void Label::draw()
{
	sf::Text t(text);
	t.setPosition(position->x+5, position->y+5);
	t.setCharacterSize(12);
	width = t.getGlobalBounds().width;
	height = t.getGlobalBounds().height;
	window->draw(t);
	//window->display();
}

void Label::setText(std::string newtext)
{
	text = newtext;
	draw();
}

Label::~Label()
{
	//delete window;
	delete position;
}