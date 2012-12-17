#include <SFML/Graphics.hpp>
#pragma once
class AbstractView
{
public:
	AbstractView(sf::RenderWindow *,bool);
	AbstractView(sf::RenderWindow *);
	//A renderwindowt a mainben kell megcsin�lni, mert az kell a esem�nykezel�s miatt ,
	//amit ugye sz�t k�ne v�lasztani, mondjuk egy controllba(logika).
	virtual ~AbstractView(void);
	virtual void drawEverything() = 0;
	void addDebugInfo(std::string);
protected:
	std::vector<std::string> debugMessages;
	sf::RenderWindow *window;
	bool debugMode;

};

