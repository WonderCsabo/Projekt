#include "View.h"
#include "../Util/Utils.h"
#include "RandomColor.h"
#include <exception>
#include <cstdlib>
#include <ctime>

View::View(sf::RenderWindow *rw, bool deb):AbstractView(rw,deb)
{
  init();
}
View::View(sf::RenderWindow *rw) : AbstractView(rw)
{
  init();
}
void View::addText(sf::Text text)
{
  texts.push_back(text);
}
void View::init()
{
  debugBox = new sf::RectangleShape();
  debug = new sf::Text();
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

  if (!mapTexture.loadFromFile("resource/map.jpg"))
    std::cout<<"map cannon could not be loaded";
  mapSprite.setTexture(mapTexture);
  mapSprite.setPosition(0.0f,0.0f);


  barrelTextures.addTexture(texture1);
  barrelTextures.addTexture(texture2);
  barrelTextures.addTexture(texture3);
  tankTextures->addTexture(texture4);
  tankTextures->addTexture(texture5);
  tankTextures->addTexture(texture6);
}
void View::addTank(CommonTankInfo* tank)
{
  bool hasColor = false;
  for(unsigned i = 0; i < teamColors.size(); i++)
    {
      if(i == tank->team()) hasColor = true;
    }
  if(!hasColor)
    {
      teamColors.resize(tank->team()+1);
      teamColors[tank->team()] = RandomColor::getRandomColor();
    }
  //TankAnimation(Tank*,TextureHolder*, sf::Color);
  //new TankAnimaton(tank, tankTextures, teamColors[t->team])
  tanks.push_back((new TankAnimation(tank, tankTextures,cannonTexture,selection, teamColors[tank->team()])));
  //tanks.push_back((new TankAnimation(tank, tankTextures, )));
}
void View::updateTanks()
{
  for(unsigned i = 0; i < tanks.size(); i++)
    {
      tanks[i]->updateTank();
    }
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
  debugBox->setSize(sf::Vector2f(200.0f,8+12.0f*(float)debugMessages.size()));
  debug->setString(message);
  debug->setPosition(510,8);
  debug->setCharacterSize(10);
  debug->setColor(sf::Color(255,255,255));
  window->draw(*debugBox);
  window->draw(*debug);
}
void View::drawTank()
{
  for(unsigned i = 0; i < tanks.size(); i++)
    {
	  if(tanks[i]->isSelected())
		  window->draw(*(tanks[i]->getSelection()));
      window->draw(*(tanks[i]->getTank()));
      window->draw(*(tanks[i]->getCannon()));
    }
}
void View::clearBackground()
{
  window->clear();
  window->draw(mapSprite);
}
void View::drawBarrels()
{
  for(unsigned i = 0; i< barrels.size(); i++)
    window->draw(*barrels[i]);
}
void View::addBarrel(float posX, float posY, float dimX, float dimY)
{

  sf::Sprite *barrel = new sf::Sprite();
  barrel->setTexture(*barrelTextures.returnRandom());
  barrel->setPosition(posX, posY);
  barrel->setScale(dimX/barrel->getTexture()->getSize().x, dimY/barrel->getTexture()->getSize().y);
  barrel->setOrigin(dimX/2, dimY/2);
  barrel->setRotation((float)(std::rand()%350));
  barrel->setColor(sf::Color(std::rand()%255,std::rand()%255,std::rand()%255));
  //std::cout<<"Barrel added on ("<<posX<<","<<posY<<") size:["<<dimX<<","<<dimY<<"]\n";
  barrels.push_back(barrel);
}
void View::drawTexts()
{
  for(unsigned i = 0; i< texts.size(); i++)
    window->draw(texts[i]);
}
void View::drawEverything()
{
  updateTanks();
  clearBackground();
  drawBarrels();
  drawTank();
  drawDebug();
  drawTexts();
  window->display();
}
View::~View(void)
{
  delete debugBox;
  delete debug;

  clearPointerContainer(barrels);

  barrelTextures.clear();
  delete tankTextures;
  delete cannonTexture;
  delete selection;
}
