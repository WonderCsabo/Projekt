#include "View.h"
#include <exception>
#include <cstdlib>
#include <ctime>
View::View(sf::RenderWindow *rw, bool deb):AbstractView(rw,deb) 
{
	init();
}
View::View(sf::RenderWindow *rw) : AbstractView(rw) {
	init();
}
void View::init()
{
	debugBox = new sf::RectangleShape();
	debug = new sf::Text();
	 sf::Texture *texture1 = new sf::Texture();
	 if (!texture1->loadFromFile("resource/barrel1.png"))
		 std::cout<<"barrel1 could not be loaded";
	 sf::Texture *texture2 = new sf::Texture();
	 if (!texture2->loadFromFile("resource/barrel2.png"))
		 std::cout<<"barrel2 could not be loaded";
	 sf::Texture *texture3 = new sf::Texture();
	 if (!texture3->loadFromFile("resource/barrel3.png"))
	 std::cout<<"barrel2 could not be loaded";
	 barrelTextures.addTexture(texture1);
	 barrelTextures.addTexture(texture2);
	 barrelTextures.addTexture(texture3);
}
void View::drawDebug()
{
	if(debugMode == false) return;	
	debugBox->setPosition(500,0);
	debugBox->setFillColor(sf::Color(40,40,40,128));
	std::string message;
	if (debugMessages.size()>24)
		debugMessages.pop_front();
	for (std::list<std::string>::iterator it = debugMessages.begin(); it!=debugMessages.end(); it++)
		message+=(*it)+"\n";
	debugBox->setSize(sf::Vector2f(200,13*debugMessages.size()));
	debug->setString(message);
	debug->setPosition(510,8);
	debug->setCharacterSize(10);
	debug->setColor(sf::Color(255,255,255));
	window->draw(*debugBox);
	window->draw(*debug);
}
void View::clearBackground()
{
	window->clear();
}
void View::drawBarrels()
{
	for(int i = 0; i< barrels.size(); i++)
		window->draw(*barrels[i]);
}
void View::addBarrel(float posX, float posY, float dimX, float dimY)
{
	std::cout<<"Barrel added on:" <<posX << ", " <<posY<<std::endl;
	sf::Sprite *barrel = new sf::Sprite();
	barrel->setTexture(*barrelTextures.returnRandom());
	barrel->setPosition(posX, posY);
	barrel->setScale(dimX, dimY);
	barrel->setOrigin(dimX/2, dimY/2);
	barrel->setRotation(std::rand()%350);
	barrel->setColor(sf::Color::Color(std::rand()%255,std::rand()%255,std::rand()%255));
	barrels.push_back(barrel);
}
void View::drawEverything()
{
	clearBackground();
	drawBarrels();
	drawDebug();
}
View::~View(void)
{
	delete debugBox;
	delete debug;
	for(int i = 0; i< barrels.size(); i++)
		delete barrels[i];
	barrelTextures.clear();
}
