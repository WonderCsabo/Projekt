#include "View.h"
#include "../Util/Utils.h"
#include "RandomColor.h"
#include <cstdlib>
#include <ctime>

View::View(sf::RenderWindow *rw) : AbstractView(rw)
{
	init();
}
View::~View(void)
{
	clearPointerContainer(barrels);
	clearPointerContainer(tanks);
	delete tankTextures;
	delete cannonTexture;
	delete selection;
	delete bulletTexture;
	delete bummTextures;
}

void View::addBarrel(const sf::Vector2f& position,const sf::Vector2f& dimension)
{

	sf::Sprite *barrel = new sf::Sprite();
	barrel->setTexture(*barrelTextures.returnRandom());
	barrel->setPosition(position);
	barrel->setScale(dimension.x/barrel->getTexture()->getSize().x, dimension.y/barrel->getTexture()->getSize().y);
	barrel->setOrigin(dimension.x/2, dimension.y/2);
	barrel->setRotation((float)(std::rand()%350));
	barrel->setColor(sf::Color(std::rand()%255,std::rand()%255,std::rand()%255));
	barrels.push_back(barrel);
}

void View::addTank(CommonTankInfo* tank)
{
	bool hasColor = false;
	for(unsigned i = 0; i < teamColors.size(); i++)
	{
		if(i == tank->getTeamId()) hasColor = true;
	}
	if(!hasColor)
	{
		teamColors.resize(tank->getTeamId()+1);
		teamColors[tank->getTeamId()] = RandomColor::getRandomColor();
	}
	tanks.push_back((new TankAnimation(tank, tankTextures,bummTextures,cannonTexture,selection,bulletTexture, teamColors[tank->getTeamId()])));
}
void View::drawEverything()
{
	updateTanks();
	clearBackground();
	drawBarrels();
	drawTank();
	drawInputChat();
	drawOutputChat();
	window->display();
}
void View::updateTanks()
{
	for(unsigned i = 0; i < tanks.size(); i++)
	{
		tanks[i]->updateTank();
	}
}
void View::drawTank()
{
	for(unsigned i = 0; i < tanks.size(); i++)
	{
		if(tanks[i]==NULL) continue;
		if(tanks[i]->isDestroyed())
		{
			sf::Sprite *sprite = tanks[i]->getBumm();
			if(sprite != NULL)
				window->draw(*sprite);
			else
				{
					delete tanks[i];
					tanks.erase(tanks.begin()+i);
				}
			continue;
		}
		if(tanks[i]->isSelected())
			window->draw(*(tanks[i]->getSelection()));
		window->draw(*tanks[i]->getBullet());
		window->draw(*(tanks[i]->getTank()));
		window->draw(*(tanks[i]->getCannon()));

	}
}
void View::drawBarrels()
{
	for(unsigned i = 0; i< barrels.size(); i++)
		window->draw(*barrels[i]);
}
void View::drawInputChat()
{
	window->draw(inputChatBackground);
	inputChatText.setString(inputText);
	window->draw(inputChatText);
}
void View::drawOutputChat()
{
	outputChatBackground.setSize(sf::Vector2f(200.0f,8+12.0f*(float)outputText.size()));
	//if(outputText.size() == 0) return;

	std::string message = "";
	for(std::list<std::string>::iterator iter = outputText.begin(); iter != outputText.end();iter++)
		message += (*iter) + "\n";
	outputChatText.setString(message);
	window->draw(outputChatBackground);
	window->draw(outputChatText);
}
void View::clearBackground()
{
	window->clear();
	window->draw(mapSprite);
}
void View::init()
{
	outputChatBackground.setPosition(sf::Vector2f(500.0f, 0.0f));
	outputChatBackground.setFillColor(sf::Color(40,40,40,128));
	outputChatText.setPosition(sf::Vector2f(510.0f, 8.0f));
	outputChatText.setCharacterSize(10);
	outputChatText.setColor(sf::Color::White);
	inputChatBackground.setPosition(sf::Vector2f(0.0f, 0.0f));
	inputChatBackground.setFillColor(sf::Color(40,40,40,128));
	inputChatBackground.setSize(sf::Vector2f(200.0f, 28.0f));
	inputChatText.setPosition(sf::Vector2f(10.0f, 8.0f));
	inputChatText.setColor(sf::Color::White);
	inputChatText.setCharacterSize(10);
	tankTextures = new TextureHolder();
	sf::Texture *texture1 = new sf::Texture();
	if (!texture1->loadFromFile("resource/barrel1.png"))
		std::cout<<"barrel1 could not be loaded";
	sf::Texture *texture2 = new sf::Texture();
	if (!texture2->loadFromFile("resource/barrel2.png"))
		std::cout<<"barrel2 could not be loaded";
	sf::Texture *texture3 = new sf::Texture();
	if (!texture3->loadFromFile("resource/barrel3.png"))
		std::cout<<"barrel2 could not be loaded";
	sf::Texture *texture4 = new sf::Texture();
	if (!texture4->loadFromFile("resource/tank1.png"))
		std::cout<<"tank1 could not be loaded";

	sf::Texture *texture5 = new sf::Texture();
	if (!texture5->loadFromFile("resource/tank2.png"))
		std::cout<<"tank2 could not be loaded";

	sf::Texture *texture6 = new sf::Texture();
	if (!texture6->loadFromFile("resource/tank3.png"))
		std::cout<<"tank3 could not be loaded";

	cannonTexture = new sf::Texture();
	if (!cannonTexture->loadFromFile("resource/cannon.png"))
		std::cout<<"cannon cannon could not be loaded";

	selection = new sf::Texture();
	if (!selection->loadFromFile("resource/selection.png"))
		std::cout<<"selection could not be loaded";

	bulletTexture = new sf::Texture();
	if (!bulletTexture->loadFromFile("resource/bullet.png"))
		std::cout<<"bullet could not be loaded";
	else std::cout<<"pedig betöltöm";

	if (!mapTexture.loadFromFile("resource/map.jpg"))
		std::cout<<"map cannon could not be loaded";
	mapSprite.setTexture(mapTexture);
	mapSprite.setPosition(0.0f,0.0f);

		bummTextures = new TextureHolder();
	sf::Texture *bumm1 = new sf::Texture();
	if (!bumm1->loadFromFile("resource/bumm1.png"))
		std::cout<<"bumm1 could not be loaded";
	sf::Texture *bumm2 = new sf::Texture();
	if (!bumm2->loadFromFile("resource/bumm2.png"))
		std::cout<<"bumm2 could not be loaded";
	sf::Texture *bumm3 = new sf::Texture();
	if (!bumm3->loadFromFile("resource/bumm3.png"))
		std::cout<<"bumm3 could not be loaded";
	sf::Texture *bumm4 = new sf::Texture();
	if (!bumm4->loadFromFile("resource/bumm4.png"))
		std::cout<<"bumm4 could not be loaded";

	barrelTextures.addTexture(texture1);
	barrelTextures.addTexture(texture2);
	barrelTextures.addTexture(texture3);
	tankTextures->addTexture(texture4);
	tankTextures->addTexture(texture5);
	tankTextures->addTexture(texture6);
	bummTextures->addTexture(bumm1);
	bummTextures->addTexture(bumm2);
	bummTextures->addTexture(bumm3);
	bummTextures->addTexture(bumm4);
}
