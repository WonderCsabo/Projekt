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
	void addOutputChat(const std::string&);
	void addInputChat(const std::string&);

protected:
	sf::RenderWindow *window;
	std::string inputText;
	std::list<std::string> outputText;
};

