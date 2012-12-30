#pragma once
#include "../Controller/CommonTankInfo.h"
#include <SFML/Graphics.hpp>
#include <list>

class AbstractView
{
public:
	AbstractView(sf::RenderWindow *);
	virtual ~AbstractView(void);
	virtual void drawEverything() = 0;
	virtual void addBarrel(const sf::Vector2f&,const sf::Vector2f&) = 0;
	virtual void addTank(CommonTankInfo*) = 0;
protected:
	sf::RenderWindow *window;
};

