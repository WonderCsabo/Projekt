#pragma once
#ifndef LABEL_H
#define LABEL_H

#include "guielement.h"

class Label : public GuiElement
{
public:
	Label(std::string, sf::RenderWindow*, Coord*, std::string);
	virtual ~Label();
	virtual void setText(std::string);
	virtual void draw();

protected:

};

#endif //LABEL_H