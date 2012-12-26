#pragma once
#ifndef EDITBOX_H
#define EDITBOX_H

#include "Label.h"

class EditBox : public Label
{
public:
	EditBox(std::string, sf::RenderWindow*, Coord*, std::string, int, int);
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

#endif //EDITBOX_H