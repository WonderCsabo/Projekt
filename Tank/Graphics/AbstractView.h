#pragma once

#include <SFML/Graphics.hpp>
#include <list>

class AbstractView
{
public:
	AbstractView(sf::RenderWindow *,bool);
	AbstractView(sf::RenderWindow *);
	//A renderwindowt a mainben kell megcsinálni, mert az kell a eseménykezelés miatt ,
	//amit ugye szét kéne választani, mondjuk egy controllba(logika).
	virtual ~AbstractView(void);
	virtual void drawEverything() = 0;
	void addDebugInfo(std::string);
	virtual void addBarrel(float, float, float, float) = 0;
protected:
	std::list<std::string> debugMessages;
	sf::RenderWindow *window;
	bool debugMode;

};

