#include "View.h"
#include <exception>

View::View(sf::RenderWindow *rw, bool deb):AbstractView(rw,deb) 
{
	temp = new sf::Texture();
	generateBackground("resource/map.png");
}
View::View(sf::RenderWindow *rw) : AbstractView(rw) {
	temp = new sf::Texture();
	generateBackground("resource/map.png");
}

void View::generateBackground(std::string filename)
{
	if(!temp->loadFromFile(filename))
	{
		throw new std::exception("nincs meg a fajl");
	}
	background = new sf::Sprite(*temp);
}
void View::drawDebug()
{
	if(debugMode == false) return;
	sf::RectangleShape box(sf::Vector2f(200,300));
	box.setPosition(500,0);
	box.setFillColor(sf::Color(0,0,0,128));
	std::string message;
	if (debugMessages.size()>24)
		debugMessages.pop_front();
	for (std::list<std::string>::iterator it = debugMessages.begin(); it!=debugMessages.end(); it++)
		message+=(*it)+"\n";
	sf::Text debug(message);
	debug.setPosition(510,8);
	debug.setCharacterSize(10);
	debug.setColor(sf::Color(255,255,255));
	window->draw(box);
	window->draw(debug);
}
void View::drawBackground()
{
	window->draw(*background);
}
void View::drawEverything()
{
	window->clear();
	drawBackground();
	drawDebug();
	//window->display();
}
View::~View(void)
{
}
