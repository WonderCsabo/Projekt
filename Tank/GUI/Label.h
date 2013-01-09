#pragma once

#include "GuiElement.h"

class Label : public GuiElement
{
public:
    Label(std::string, sf::RenderWindow*, Coord, std::string);
    virtual ~Label();
    virtual void setText(std::string);
    virtual void draw();

protected:

};
