#pragma once

#include <list>
#include "GuiElement.h"
#include "EditBox.h"
#include "Label.h"
#include "Button.h"

class GuiContainer
{
public:
	GuiContainer(sf::RenderWindow* rw) : window(rw) {};

	void add(GuiElement* e)
	{
		elements.push_back(e);
	}

	GuiElement* isClicked(sf::Event& ev)
	{
		for (std::list<GuiElement*>::iterator it = elements.begin(); it!=elements.end(); it++)
		{
			if ((**it).isMouseClicked(ev))
			{
				if ((**it).getType()==GuiElement::EDT)
				{
					EditBox* e = static_cast<EditBox*>(*it);
					for (std::list<GuiElement*>::iterator it = elements.begin(); it!=elements.end(); it++) {
						if ((**it).getType() == GuiElement::EDT) {
							EditBox* tmp = static_cast<EditBox*>(*it);
							tmp->setFocused(false);
						}
					}
					e->setFocused(true);
				}
				return *it;
			}
		}
		return NULL;
	}

	void type(sf::Event& ev)
	{
		bool* next = NULL;
		for (std::list<GuiElement*>::iterator it = elements.begin(); it!=elements.end(); it++)
		{
			if ((**it).getType()==GuiElement::EDT)
			{
				EditBox* e = static_cast<EditBox*>(*it);
				if (e->isFocused())
				{
					e->type(ev);
				}
			}
		}
		if (next!=NULL) delete next;
	}

	void draw()
	{
		window->clear();
		for (std::list<GuiElement*>::iterator it = elements.begin(); it!=elements.end(); it++)
		{
			(**it).draw();
		}
		window->display();
	}

	~GuiContainer()
	{
		for (std::list<GuiElement*>::iterator it = elements.begin(); it!=elements.end(); it++)
		{
			delete *it;
		}
	}

private:
	std::list<GuiElement*> elements;
	sf::RenderWindow* window;
};