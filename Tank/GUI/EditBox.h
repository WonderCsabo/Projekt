#pragma once

#include "Label.h"

class EditBox : public Label
{
public:
	EditBox(std::string, sf::RenderWindow*, Coord*, std::string, float, float);
	virtual ~EditBox();
	virtual void draw();
	bool isFocused();
	void setFocused(bool);
	virtual void type(sf::Event&);
	//virtual void onClick(void());

protected:
	virtual void type(char);
	virtual void backspace();
	bool focused;

private:
	sf::RectangleShape* rect;
};