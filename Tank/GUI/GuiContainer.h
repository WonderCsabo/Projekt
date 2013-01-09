#pragma once

#include <list>
#include "GuiElement.h"
#include "EditBox.h"
#include "Label.h"
#include "Button.h"

class GuiContainer
{
public:
    GuiContainer(sf::RenderWindow*);
    ~GuiContainer();

    void add(GuiElement*);
    GuiElement* isClicked(sf::Event&);
    void type(sf::Event&);
    void draw();

private:
    std::list<GuiElement*> elements;
    sf::RenderWindow* window;
};