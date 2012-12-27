#include "GuiContainer.h"
#include "../Util/Utils.h"

GuiContainer::GuiContainer(sf::RenderWindow* rw) : window(rw) {}

GuiContainer::~GuiContainer()
{
	clearPointerContainer(elements);
}

void GuiContainer::add(GuiElement* e)
{
	elements.push_back(e);
}

void GuiContainer::draw()
{
	window->clear();
	for (std::list<GuiElement*>::iterator it = elements.begin(); it!=elements.end(); it++)
	{
		(**it).draw();
	}
	window->display();
}

void GuiContainer::type(sf::Event& ev)
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

GuiElement* GuiContainer::isClicked(sf::Event& ev)
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
