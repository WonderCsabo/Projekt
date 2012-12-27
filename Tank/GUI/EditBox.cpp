#include "EditBox.h"

EditBox::EditBox(std::string id_, sf::RenderWindow* rw, Coord* pos, std::string txt, float w, float h) : Label(id_, rw, pos, txt)
{
	TYPE = GuiElement::EDT;
	width = w;
	height = h;
	rect = new sf::RectangleShape;
	sf::Vector2f v(width,height);
	rect->setSize(v);
	rect->setFillColor(sf::Color(255,255,255));
	rect->setPosition(position->x, position->y);
	draw();
	focused = false;
}

EditBox::~EditBox()
{
	delete rect;
}

/*void EditBox::onClick(void (*func)())
{
	(*func)();
}*/

bool EditBox::isFocused()
{
	return focused;
}

void EditBox::type(sf::Event& ev)
{
	if (ev.type == ev.KeyPressed) {
		char* c = NULL;
		if (ev.key.code>=0 && ev.key.code<=25) {
			
			if (ev.key.shift==false)
				c = new char(97+ev.key.code);
			else
				c = new char(65+ev.key.code);
			type(*c);
		}
		else if (ev.key.code==sf::Keyboard::Space)
			type(' ');
		else if (ev.key.code>=26 && ev.key.code<=35)
		{
			c = new char(48+ev.key.code-26);
			type(*c);
		}
		else if (ev.key.code>=75 && ev.key.code<=84)
		{
			c = new char(48+ev.key.code-75);
			type(*c);
		}
		else if (ev.key.code == sf::Keyboard::Period)
			type('.');
		else if (ev.key.code == sf::Keyboard::Back)
			backspace();

		if (c!=NULL) delete c;
	}
}

void EditBox::setFocused(bool f)
{
	focused = f;
}

void EditBox::type(char c)
{
	if (focused)
		text+=c;
	draw();
}

void EditBox::backspace()
{
	text = text.substr(0, text.length()-1);
	draw();
}

void EditBox::draw()
{
	sf::Text t(text);
	t.setPosition(position->x+5, position->y+5);
	t.setCharacterSize(12);
	t.setColor(sf::Color(0, 0, 0));
	window->draw(*rect);
	window->draw(t);
}