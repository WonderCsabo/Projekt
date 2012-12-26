#pragma once
#include "abstractview.h"
#include <string>
class View :
	public AbstractView
{
public:
	void drawEverything();
	View(sf::RenderWindow *, bool);
	View(sf::RenderWindow *rw);
	~View(void);
private:
	void drawDebug();
	void drawBackground();
	void generateBackground(std::string);
	sf::Sprite *background;//map
	sf::Texture *temp;
};

